/****************************************************************************
 * arch/arm/src/ra8/ra_ether.c
 *
 * RA8P1 Layer 3 Ethernet Switch Driver for NuttX
 *
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.  The
 * ASF licenses this file to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance with the
 * License.  You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  See the
 * License for the specific language governing permissions and limitations
 * under the License.
 *
 ****************************************************************************/

/****************************************************************************
 * RA8P1 Layer 3 Ethernet Switch Architecture
 *
 * The RA8P1 uses a Layer 3 Ethernet Switch, NOT the traditional ETHERC/EDMAC.
 * The architecture consists of:
 *
 *   COMA (0x403c9000) - Common Agent
 *     - Software reset via RRC register
 *     - Root clock enable via RCEC register
 *     - Buffer pool initialization monitoring via CABPIRM
 *
 *   GWCA (0x403ce000) - Gateway CPU Agent
 *     - CPU interface for TX/RX
 *     - Mode control: GWMC/GWMS registers
 *     - Descriptor chain management: GWDCC[], GWDCBAC[], etc.
 *     - Data interrupt: GWDI/GWDIE
 *
 *   ETHA (0x403ca000, stride 0x2000) - Ethernet Agent (per port)
 *     - TX descriptor queue management
 *     - Mode control: EAMC/EAMS registers
 *     - TSN/TAS support
 *
 *   RMAC (0x403cb000, stride 0x2000) - MAC (per port)
 *     - PHY interface: MPIC register (MII/RMII/RGMII)
 *     - PHY management: MPSM register (MDIO read/write)
 *     - MAC address: MRMAC0/MRMAC1 registers
 *
 * Initialization Sequence (from FSP r_ether.c):
 *   1. Clear MSTP bits for Ether-PHY clock and Layer 3 Switch
 *   2. COMA software reset (RRC = 1, then RRC = 0)
 *   3. Enable COMA root clock (RCEC.RCE = 1)
 *   4. Wait for buffer pool initialization (CABPIRM.BPIOG = 1)
 *   5. Transition GWCA: RESET -> DISABLE -> CONFIG -> OPERATION
 *   6. Transition ETHA: RESET -> DISABLE -> CONFIG -> OPERATION
 *   7. Configure RMAC: PHY interface, MAC address
 *   8. Initialize PHY via MDIO
 *   9. Configure descriptor chains
 *   10. Enable interrupts
 *
 ****************************************************************************/

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>

#include <inttypes.h>
#include <stdint.h>
#include <stdbool.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <assert.h>
#include <debug.h>
#include <errno.h>

#include <arpa/inet.h>

#include <nuttx/wdog.h>
#include <nuttx/irq.h>
#include <nuttx/arch.h>
#include <nuttx/wqueue.h>
#include <nuttx/net/mii.h>
#include <nuttx/net/phy.h>
#include <nuttx/net/netdev.h>

#ifdef CONFIG_NET_ARP
#  include <nuttx/net/arp.h>
#endif

#ifdef CONFIG_NET_PKT
#  include <nuttx/net/pkt.h>
#endif

#include "arm_internal.h"
#include "barriers.h"
#include "chip.h"
#include "ra_ether.h"

/* Layer 3 Ethernet Switch hardware headers */
#include "hardware/ra8p1/ra_coma.h"
#include "hardware/ra8p1/ra_gwca.h"
#include "hardware/ra8p1/ra_etha.h"
#include "hardware/ra8p1/ra_rmac.h"

#include "ra_icu.h"
#include "ra_mstp.h"

#ifdef CONFIG_RA_ETHERNET

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* Configuration ************************************************************/

#ifndef CONFIG_RA_ETHERNET_NINTERFACES
#  define CONFIG_RA_ETHERNET_NINTERFACES 1
#endif

#ifndef CONFIG_RA_ETHERNET_NTXDESC
#  define CONFIG_RA_ETHERNET_NTXDESC 8
#endif

#ifndef CONFIG_RA_ETHERNET_NRXDESC
#  define CONFIG_RA_ETHERNET_NRXDESC 8
#endif

#define RA_MAX_PACKET_SIZE  1536
#define RA_BUF_ALIGN        32
#define RA_DESC_ALIGN       16

/* GWCA/ETHA Operation Mode timeout (milliseconds) */
#define RA_MODE_TIMEOUT_MS  100

/* COMA Buffer Pool Init timeout (milliseconds) */
#define RA_BPOOL_TIMEOUT_MS 100

/* PHY MDIO operation timeout (milliseconds) */
#define RA_PHY_TIMEOUT_MS   10

/* GWCA Descriptor Queue indices
 * TX queues: 0-31, RX queues: 32-63
 */
#define RA_GWCA_TX_QUEUE    0
#define RA_GWCA_RX_QUEUE    32

/* ELC Events for Ethernet Interrupts (from ra8p1_irq.h)
 *
 * GWCA Data Interrupts (GWDI0-GWDI7): 0x2A6-0x2AD
 *   - 8 data interrupts corresponding to descriptor chain groups
 *   - Use GWDI0 (RA_ELC_ETHER_GWDI0) for primary data interrupt
 *
 * RMAC PHY Interrupts (RMPI0/RMPI1): 0x2B2/0x2B3
 *   - Per-port PHY link status interrupts
 *   - RMPI0 for port 0, RMPI1 for port 1
 */

/****************************************************************************
 * Private Types
 ****************************************************************************/

/* Driver state machine */
enum ra_ether_state_e
{
  RA_ETHER_STATE_UNINIT = 0,   /* Not initialized */
  RA_ETHER_STATE_RESET,        /* In reset */
  RA_ETHER_STATE_READY,        /* Initialized, link down */
  RA_ETHER_STATE_RUNNING       /* Running, link up */
};

/* The ra_ether_s encapsulates all state information for a single port */

struct ra_ether_s
{
  bool                  bifup;          /* true:ifup false:ifdown */
  struct net_driver_s   dev;            /* Interface understood by the network */
  enum ra_ether_state_e state;          /* Driver state */
  uint8_t               port;           /* Port number (0 or 1) */
  uint8_t               phyaddr;        /* PHY address */
  int                   irq_data;       /* GWCA data interrupt IRQ */
  int                   irq_phy;        /* RMAC PHY interrupt IRQ */

  /* Configuration */
  ra_ether_phy_mode_t   phy_mode;       /* PHY interface mode */
  ra_ether_speed_t      speed;          /* Link speed */
  ra_ether_duplex_t     duplex;         /* Duplex mode */
  uint8_t               mac[6];         /* MAC address */

  /* TX Descriptor Chain */
  struct ra_eth_desc_s  *txdesc;
  uint8_t               *txbuffer;
  uint16_t              txhead;         /* Next TX descriptor to use */
  uint16_t              txtail;         /* Next TX descriptor to reclaim */

  /* RX Descriptor Chain */
  struct ra_eth_desc_s  *rxdesc;
  uint8_t               *rxbuffer;
  uint16_t              rxhead;         /* Next RX descriptor with data */

  /* Link descriptor pointers (point to DTCM-located link descriptors) */
  struct ra_eth_desc_s  *txlink;        /* TX chain link back to start */
  struct ra_eth_desc_s  *rxlink;        /* RX chain link back to start */
};

/****************************************************************************
 * Private Data
 ****************************************************************************/

static struct ra_ether_s g_ra_ether[CONFIG_RA_ETHERNET_NINTERFACES];

/* Static flag to track if shared resources (COMA, GWCA) are initialized */
static bool g_l3switch_initialized = false;

/* Aligned descriptors and buffers (per-interface for multi-port support)
 *
 * These are placed in DTCM (Data Tightly Coupled Memory) which is
 * non-cacheable on Cortex-M85. This avoids cache coherency issues
 * between CPU and DMA without requiring cache maintenance operations.
 *
 * The .dtcm_noinit section is defined in the linker script as a NOLOAD
 * section in DTCM memory region, meaning these buffers won't be initialized
 * at startup (which is fine for DMA buffers).
 *
 * Memory layout in DTCM (per interface, multiply by NINTERFACES for total):
 *   g_txdesc:   8 * 16 =   128 bytes per interface
 *   g_rxdesc:   8 * 16 =   128 bytes per interface
 *   g_txlink:   1 * 16 =    16 bytes per interface
 *   g_rxlink:   1 * 16 =    16 bytes per interface
 *   g_txbuffer: 8 * 1536 = 12,288 bytes per interface
 *   g_rxbuffer: 8 * 1536 = 12,288 bytes per interface
 *   Total: ~24KB per interface in DTCM
 */
static struct ra_eth_desc_s
  g_txdesc[CONFIG_RA_ETHERNET_NINTERFACES][CONFIG_RA_ETHERNET_NTXDESC]
  __attribute__((section(".dtcm_noinit"), aligned(RA_DESC_ALIGN)));
static struct ra_eth_desc_s
  g_rxdesc[CONFIG_RA_ETHERNET_NINTERFACES][CONFIG_RA_ETHERNET_NRXDESC]
  __attribute__((section(".dtcm_noinit"), aligned(RA_DESC_ALIGN)));
static struct ra_eth_desc_s g_txlink[CONFIG_RA_ETHERNET_NINTERFACES]
  __attribute__((section(".dtcm_noinit"), aligned(RA_DESC_ALIGN)));
static struct ra_eth_desc_s g_rxlink[CONFIG_RA_ETHERNET_NINTERFACES]
  __attribute__((section(".dtcm_noinit"), aligned(RA_DESC_ALIGN)));
static uint8_t
  g_txbuffer[CONFIG_RA_ETHERNET_NINTERFACES]
            [CONFIG_RA_ETHERNET_NTXDESC * RA_MAX_PACKET_SIZE]
  __attribute__((section(".dtcm_noinit"), aligned(RA_BUF_ALIGN)));
static uint8_t
  g_rxbuffer[CONFIG_RA_ETHERNET_NINTERFACES]
            [CONFIG_RA_ETHERNET_NRXDESC * RA_MAX_PACKET_SIZE]
  __attribute__((section(".dtcm_noinit"), aligned(RA_BUF_ALIGN)));

/****************************************************************************
 * Private Function Prototypes
 ****************************************************************************/

/* Layer 3 Switch initialization */
static int  ra_l3switch_init(void);
static int  ra_coma_init(void);
static int  ra_gwca_init(void);
static int  ra_gwca_set_mode(uint32_t mode);
static int  ra_etha_init(int port);
static int  ra_etha_set_mode(int port, uint32_t mode);
static int  ra_rmac_init(struct ra_ether_s *priv);

/* Descriptor management */
static void ra_init_descriptors(struct ra_ether_s *priv);
static void ra_setup_txdesc(struct ra_ether_s *priv, int idx,
                            uint8_t *buf, uint16_t len);
static void ra_setup_rxdesc(struct ra_ether_s *priv, int idx, uint8_t *buf);

/* PHY management via RMAC MPSM */
static int  ra_phy_wait_ready(int port);

/* Common TX logic */
static int  ra_txpoll(struct net_driver_s *dev);
static void ra_transmit(struct ra_ether_s *priv);

/* Interrupt handling */
static void ra_receive(struct ra_ether_s *priv);
static int  ra_data_interrupt(int irq, void *context, void *arg);
static int  ra_phy_interrupt(int irq, void *context, void *arg);

/* NuttX callback functions */
static int  ra_ifup(struct net_driver_s *dev);
static int  ra_ifdown(struct net_driver_s *dev);
static int  ra_txavail(struct net_driver_s *dev);
#ifdef CONFIG_NET_MCASTGROUP
static int  ra_addmac(struct net_driver_s *dev, const uint8_t *mac);
static int  ra_rmmac(struct net_driver_s *dev, const uint8_t *mac);
#endif
#ifdef CONFIG_NETDEV_IOCTL
static int  ra_ioctl(struct net_driver_s *dev, int cmd, unsigned long arg);
#endif

/****************************************************************************
 * Private Functions
 ****************************************************************************/

/****************************************************************************
 * Name: ra_l3switch_init
 *
 * Description:
 *   Initialize the Layer 3 Ethernet Switch shared components (COMA, GWCA).
 *   This is called once for the first port initialization.
 *
 ****************************************************************************/

static int ra_l3switch_init(void)
{
  int ret;

  if (g_l3switch_initialized)
    {
      return OK;
    }

  ninfo("Initializing Layer 3 Ethernet Switch\n");

  /* Step 1: Enable MSTP clocks for Ethernet
   * - MSTPCRC bit 28: Ether-PHY clock
   * - MSTPCRC bit 30: Layer 3 Ethernet Switch
   */

  ra_mstp_start(RA_MSTP_ETHER_PHY_CLK);
  ra_mstp_start(RA_MSTP_LAYER3_SWITCH);

  /* Step 2: Initialize COMA (reset and clock enable) */

  ret = ra_coma_init();
  if (ret < 0)
    {
      nerr("COMA initialization failed: %d\n", ret);
      return ret;
    }

  /* Step 3: Initialize GWCA */

  ret = ra_gwca_init();
  if (ret < 0)
    {
      nerr("GWCA initialization failed: %d\n", ret);
      return ret;
    }

  g_l3switch_initialized = true;
  ninfo("Layer 3 Ethernet Switch initialized\n");
  return OK;
}

/****************************************************************************
 * Name: ra_coma_init
 *
 * Description:
 *   Initialize the COMA (Common Agent) module.
 *   - Assert and deassert software reset
 *   - Enable root clock
 *   - Wait for buffer pool initialization
 *
 ****************************************************************************/

static int ra_coma_init(void)
{
  uint32_t timeout;
  uint32_t regval;

  ninfo("Initializing COMA\n");

  /* Step 1: Assert software reset (RRC.RR = 1) */

  putreg32(R_COMA_RRC_RR, R_COMA_RRC);

  /* Brief delay for reset assertion */

  up_udelay(10);

  /* Step 2: Deassert software reset (RRC.RR = 0) */

  putreg32(0, R_COMA_RRC);

  /* Step 3: Enable root clock (RCEC.RCE = 1) */

  putreg32(R_COMA_RCEC_RCE, R_COMA_RCEC);

  /* Step 4: Wait for buffer pool initialization (CABPIRM.BPIOG = 1)
   * The buffer pool must be initialized before any other operations.
   */

  timeout = RA_BPOOL_TIMEOUT_MS;
  while (timeout > 0)
    {
      regval = getreg32(R_COMA_CABPIRM);
      if (regval & R_COMA_CABPIRM_BPIOG)
        {
          ninfo("COMA buffer pool initialized\n");
          return OK;
        }

      up_mdelay(1);
      timeout--;
    }

  nerr("COMA buffer pool initialization timeout\n");
  return -ETIMEDOUT;
}

/****************************************************************************
 * Name: ra_gwca_set_mode
 *
 * Description:
 *   Set GWCA operation mode and wait for transition.
 *   Mode values: RESET(0) -> DISABLE(1) -> CONFIG(2) -> OPERATION(3)
 *
 ****************************************************************************/

static int ra_gwca_set_mode(uint32_t mode)
{
  uint32_t timeout;
  uint32_t regval;

  /* Write target mode to GWMC */

  putreg32(mode, R_GWCA_GWMC);

  /* Wait for mode transition (GWMS.OPS matches target mode) */

  timeout = RA_MODE_TIMEOUT_MS;
  while (timeout > 0)
    {
      regval = getreg32(R_GWCA_GWMS);
      if ((regval & R_GWCA_GWMS_OPS_MASK) == mode)
        {
          return OK;
        }

      up_mdelay(1);
      timeout--;
    }

  nerr("GWCA mode transition timeout (target=%lu)\n", (unsigned long)mode);
  return -ETIMEDOUT;
}

/****************************************************************************
 * Name: ra_gwca_init
 *
 * Description:
 *   Initialize the GWCA (Gateway CPU Agent) module.
 *   Transition: RESET -> DISABLE -> CONFIG
 *   (OPERATION mode is set when interface comes up)
 *
 ****************************************************************************/

static int ra_gwca_init(void)
{
  int ret;

  ninfo("Initializing GWCA\n");

  /* Transition to DISABLE mode first */

  ret = ra_gwca_set_mode(RA_ETHER_OPC_DISABLE);
  if (ret < 0)
    {
      nerr("GWCA failed to enter DISABLE mode\n");
      return ret;
    }

  /* Transition to CONFIG mode */

  ret = ra_gwca_set_mode(RA_ETHER_OPC_CONFIG);
  if (ret < 0)
    {
      nerr("GWCA failed to enter CONFIG mode\n");
      return ret;
    }

  ninfo("GWCA in CONFIG mode\n");
  return OK;
}

/****************************************************************************
 * Name: ra_etha_set_mode
 *
 * Description:
 *   Set ETHA operation mode for a specific port and wait for transition.
 *
 ****************************************************************************/

static int ra_etha_set_mode(int port, uint32_t mode)
{
  uint32_t timeout;
  uint32_t regval;
  uintptr_t eamc_addr;
  uintptr_t eams_addr;

  /* Calculate register addresses for the port */

  eamc_addr = R_ETHA_EAMC(port);
  eams_addr = R_ETHA_EAMS(port);

  /* Write target mode to EAMC */

  putreg32(mode, eamc_addr);

  /* Wait for mode transition */

  timeout = RA_MODE_TIMEOUT_MS;
  while (timeout > 0)
    {
      regval = getreg32(eams_addr);
      if ((regval & R_ETHA_EAMS_OPS_MASK) == mode)
        {
          return OK;
        }

      up_mdelay(1);
      timeout--;
    }

  nerr("ETHA[%d] mode transition timeout (target=%lu)\n",
       port, (unsigned long)mode);
  return -ETIMEDOUT;
}

/****************************************************************************
 * Name: ra_etha_init
 *
 * Description:
 *   Initialize the ETHA (Ethernet Agent) for a specific port.
 *   Transition: RESET -> DISABLE -> CONFIG
 *
 ****************************************************************************/

static int ra_etha_init(int port)
{
  int ret;

  ninfo("Initializing ETHA[%d]\n", port);

  /* Transition to DISABLE mode */

  ret = ra_etha_set_mode(port, RA_ETHER_OPC_DISABLE);
  if (ret < 0)
    {
      nerr("ETHA[%d] failed to enter DISABLE mode\n", port);
      return ret;
    }

  /* Transition to CONFIG mode */

  ret = ra_etha_set_mode(port, RA_ETHER_OPC_CONFIG);
  if (ret < 0)
    {
      nerr("ETHA[%d] failed to enter CONFIG mode\n", port);
      return ret;
    }

  ninfo("ETHA[%d] in CONFIG mode\n", port);
  return OK;
}

/****************************************************************************
 * Name: ra_rmac_init
 *
 * Description:
 *   Initialize the RMAC for a specific port.
 *   - Configure PHY interface mode (MII/RMII/RGMII)
 *   - Set MAC address
 *
 ****************************************************************************/

static int ra_rmac_init(struct ra_ether_s *priv)
{
  uint32_t mpic_val;
  uintptr_t base;
  int port = priv->port;

  ninfo("Initializing RMAC[%d]\n", port);

  base = R_RMAC_BASE + (port * R_RMAC_CH_STRIDE);

  /* Configure PHY Interface (MPIC register)
   * Bits:
   *   [1:0] PIS - PHY Interface Select: 0=MII, 1=RMII, 2=GMII, 3=RGMII
   *   [3:2] LSC - Link Speed Config: 0=10M, 1=100M, 2=1000M, 3=2500M
   *   [4]   PSMCS - (from hardware manual)
   */

  mpic_val = ((uint32_t)priv->phy_mode & 0x3);        /* PIS */
  mpic_val |= (((uint32_t)priv->speed & 0x3) << 2);   /* LSC */

  /* Set duplex mode if applicable (check hardware manual for exact bit) */

  if (priv->duplex == RA_ETHER_DUPLEX_FULL)
    {
      /* Full duplex bit - verify location in hardware manual */
      mpic_val |= (1 << 8);  /* Placeholder - verify actual bit position */
    }

  putreg32(mpic_val, base + R_RMAC_MPIC_OFFSET);

  /* Set MAC address
   * MRMAC0: Lower 32 bits (bytes 2-5)
   * MRMAC1: Upper 16 bits (bytes 0-1)
   */

  putreg32((priv->mac[2] << 24) | (priv->mac[3] << 16) |
           (priv->mac[4] << 8)  | priv->mac[5],
           base + R_RMAC_MRMAC0_OFFSET);

  putreg32((priv->mac[0] << 8) | priv->mac[1],
           base + R_RMAC_MRMAC1_OFFSET);

  ninfo("RMAC[%d] MAC=%02x:%02x:%02x:%02x:%02x:%02x\n",
        port, priv->mac[0], priv->mac[1], priv->mac[2],
        priv->mac[3], priv->mac[4], priv->mac[5]);

  return OK;
}

/****************************************************************************
 * Name: ra_phy_wait_ready
 *
 * Description:
 *   Wait for PHY MDIO operation to complete (MPSM.PSME = 0)
 *
 ****************************************************************************/

static int ra_phy_wait_ready(int port)
{
  uint32_t timeout;
  uint32_t regval;
  uintptr_t mpsm_addr;

  mpsm_addr = R_RMAC_BASE + (port * R_RMAC_CH_STRIDE) + R_RMAC_MPSM_OFFSET;

  timeout = RA_PHY_TIMEOUT_MS;
  while (timeout > 0)
    {
      regval = getreg32(mpsm_addr);
      if ((regval & R_RMAC_MPSM_PSME) == 0)
        {
          return OK;
        }

      up_udelay(100);
      timeout--;
    }

  return -ETIMEDOUT;
}

/****************************************************************************
 * Name: ra_init_descriptors
 *
 * Description:
 *   Initialize TX and RX descriptor chains for GWCA.
 *   Uses LINKFIX descriptor type for circular buffer operation.
 *
 ****************************************************************************/

static void ra_init_descriptors(struct ra_ether_s *priv)
{
  int i;
  uintptr_t buf_addr;

  ninfo("Initializing descriptors\n");

  /* Initialize TX descriptors as FEMPTY (ready for TX) */

  for (i = 0; i < CONFIG_RA_ETHERNET_NTXDESC; i++)
    {
      buf_addr = (uintptr_t)&priv->txbuffer[i * RA_MAX_PACKET_SIZE];

      priv->txdesc[i].info = RA_DESC_DT_FEMPTY;  /* Frame Empty - ready for use */
      priv->txdesc[i].ctrl = 0;
      priv->txdesc[i].buf_lo = (uint32_t)(buf_addr & 0xFFFFFFFF);
      priv->txdesc[i].buf_hi = 0;  /* 32-bit address system */
    }

  /* Set up TX link descriptor to create circular chain */

  priv->txlink->info = RA_DESC_DT_LINKFIX;
  priv->txlink->ctrl = 0;
  priv->txlink->buf_lo = (uint32_t)(uintptr_t)priv->txdesc;
  priv->txlink->buf_hi = 0;

  /* Initialize RX descriptors as FEMPTY (ready for RX) */

  for (i = 0; i < CONFIG_RA_ETHERNET_NRXDESC; i++)
    {
      buf_addr = (uintptr_t)&priv->rxbuffer[i * RA_MAX_PACKET_SIZE];

      priv->rxdesc[i].info = RA_DESC_DT_FEMPTY |
                             (RA_MAX_PACKET_SIZE << RA_DESC_DS_SHIFT);
      priv->rxdesc[i].ctrl = 0;
      priv->rxdesc[i].buf_lo = (uint32_t)(buf_addr & 0xFFFFFFFF);
      priv->rxdesc[i].buf_hi = 0;
    }

  /* Set up RX link descriptor to create circular chain */

  priv->rxlink->info = RA_DESC_DT_LINKFIX;
  priv->rxlink->ctrl = 0;
  priv->rxlink->buf_lo = (uint32_t)(uintptr_t)priv->rxdesc;
  priv->rxlink->buf_hi = 0;

  priv->txhead = 0;
  priv->txtail = 0;
  priv->rxhead = 0;

  /* Configure GWCA descriptor chain registers
   * GWDCBAC0/1: Global descriptor chain base address (upper 8 bits / lower 32 bits)
   * GWDCC[i]: Per-queue configuration
   *
   * For Cortex-M85 (32-bit addresses), GWDCBAC0 should be 0.
   * GWDCBAC1 holds the base address of the descriptor memory region.
   */

  /* Set global descriptor base address (upper 8 bits = 0 for 32-bit system) */

  putreg32(0, R_GWCA_GWDCBAC0);
  putreg32((uint32_t)(uintptr_t)priv->txdesc, R_GWCA_GWDCBAC1);

  /* TX Descriptor Chain Configuration (Queue 0)
   * EDE: Entry Data Enable
   * DQT: 0 = TX queue
   * BALR: Base Address Low Register valid
   */

  putreg32(R_GWCA_GWDCC_EDE | R_GWCA_GWDCC_BALR,
           R_GWCA_GWDCC(RA_GWCA_TX_QUEUE));

  /* RX Descriptor Chain Configuration (Queue 32)
   * EDE: Entry Data Enable
   * DQT: 1 = RX queue
   * BALR: Base Address Low Register valid
   */

  putreg32(R_GWCA_GWDCC_EDE | R_GWCA_GWDCC_DQT | R_GWCA_GWDCC_BALR,
           R_GWCA_GWDCC(RA_GWCA_RX_QUEUE));

  ninfo("Descriptors initialized: TX=%p, RX=%p\n",
        priv->txdesc, priv->rxdesc);
}

/****************************************************************************
 * Name: ra_setup_txdesc
 *
 * Description:
 *   Set up a TX descriptor for transmission.
 *
 ****************************************************************************/

static void ra_setup_txdesc(struct ra_ether_s *priv, int idx,
                            uint8_t *buf, uint16_t len)
{
  struct ra_eth_desc_s *desc = &priv->txdesc[idx];
  uintptr_t buf_addr = (uintptr_t)buf;

  /* Set up as FSINGLE (single frame in one descriptor) with data size */

  desc->info = RA_DESC_DT_FSINGLE | RA_DESC_DIE |
               ((uint32_t)len << RA_DESC_DS_SHIFT);

  /* Control word: target port selection
   * MSC bits select which port(s) to transmit on
   */

  desc->ctrl = (1 << priv->port) & RA_TXDESC_MSC_MASK;

  /* Buffer address */

  desc->buf_lo = (uint32_t)(buf_addr & 0xFFFFFFFF);
  desc->buf_hi = 0;

  /* Memory barrier to ensure descriptor write completes */

  ARM_DSB();
}

/****************************************************************************
 * Name: ra_setup_rxdesc
 *
 * Description:
 *   Set up an RX descriptor for reception.
 *
 ****************************************************************************/

static void ra_setup_rxdesc(struct ra_ether_s *priv, int idx, uint8_t *buf)
{
  struct ra_eth_desc_s *desc = &priv->rxdesc[idx];
  uintptr_t buf_addr = (uintptr_t)buf;

  /* Set up as FEMPTY (ready to receive) with max buffer size */

  desc->info = RA_DESC_DT_FEMPTY |
               (RA_MAX_PACKET_SIZE << RA_DESC_DS_SHIFT);
  desc->ctrl = 0;
  desc->buf_lo = (uint32_t)(buf_addr & 0xFFFFFFFF);
  desc->buf_hi = 0;

  ARM_DSB();
}

/****************************************************************************
 * Function: ra_transmit
 *
 * Description:
 *   Start transmission of a packet in the dev.d_buf buffer.
 *
 ****************************************************************************/

static void ra_transmit(struct ra_ether_s *priv)
{
  struct ra_eth_desc_s *txdesc;
  uint8_t *txbuf;
  uint16_t len;

  /* Get the current TX descriptor */

  txdesc = &priv->txdesc[priv->txhead];

  /* Check if descriptor is available (FEMPTY type) */

  if ((txdesc->info & RA_DESC_DT_MASK) != RA_DESC_DT_FEMPTY)
    {
      nwarn("TX descriptor not available\n");
      return;
    }

  /* Get the buffer and length */

  txbuf = &priv->txbuffer[priv->txhead * RA_MAX_PACKET_SIZE];
  len = priv->dev.d_len;

  if (len > RA_MAX_PACKET_SIZE)
    {
      len = RA_MAX_PACKET_SIZE;
    }

  /* Copy data to TX buffer */

  memcpy(txbuf, priv->dev.d_buf, len);

  /* Set up the descriptor */

  ra_setup_txdesc(priv, priv->txhead, txbuf, len);

  /* Advance TX head */

  priv->txhead++;
  if (priv->txhead >= CONFIG_RA_ETHERNET_NTXDESC)
    {
      priv->txhead = 0;
    }

  /* Trigger GWCA to process TX descriptors
   * Write to GWDCR (Descriptor Chain Request) to signal new data
   * The exact mechanism depends on hardware - may need to write
   * to a doorbell register or just let DMA poll.
   */

  /* For polling mode, GWCA will automatically pick up FSINGLE descriptors */

  ninfo("TX: len=%d, head=%d\n", len, priv->txhead);
}

/****************************************************************************
 * Function: ra_txpoll
 *
 * Description:
 *   The transmitter is available, check if the network has any outgoing
 *   packets ready to send.  This is a callback from devif_poll().
 *
 ****************************************************************************/

static int ra_txpoll(struct net_driver_s *dev)
{
  struct ra_ether_s *priv = (struct ra_ether_s *)dev->d_private;

  /* If the polling resulted in data that should be sent out on the network,
   * the field d_len is set to a value > 0.
   */

  if (priv->dev.d_len > 0)
    {
      /* Check if TX descriptor is available */

      struct ra_eth_desc_s *txdesc = &priv->txdesc[priv->txhead];

      if ((txdesc->info & RA_DESC_DT_MASK) != RA_DESC_DT_FEMPTY)
        {
          /* No descriptor available, return busy */

          return -EBUSY;
        }

      /* Transmit the packet */

      ra_transmit(priv);
    }

  return OK;
}

/****************************************************************************
 * Function: ra_receive
 *
 * Description:
 *   Process received packets from the RX descriptor chain.
 *   Called from interrupt context or polling.
 *
 ****************************************************************************/

static void ra_receive(struct ra_ether_s *priv)
{
  struct ra_eth_desc_s *rxdesc;
  uint32_t desc_type;
  uint16_t len;
  uint8_t *rxbuf = NULL;

#define BUF ((struct eth_hdr_s *)priv->dev.d_buf)

  /* Loop while there are received packets */

  while (1)
    {
      rxdesc = &priv->rxdesc[priv->rxhead];

      /* Memory barrier before reading descriptor */

      ARM_DSB();

      /* Check descriptor type */

      desc_type = rxdesc->info & RA_DESC_DT_MASK;

      /* FEMPTY means no data received yet */

      if (desc_type == RA_DESC_DT_FEMPTY)
        {
          break;
        }

      /* FSINGLE or FEND means we have a complete frame */

      if (desc_type == RA_DESC_DT_FSINGLE || desc_type == RA_DESC_DT_FEND)
        {
          /* Extract frame length from descriptor */

          len = (rxdesc->info & RA_DESC_DS_MASK) >> RA_DESC_DS_SHIFT;

          /* Get buffer pointer */

          rxbuf = &priv->rxbuffer[priv->rxhead * RA_MAX_PACKET_SIZE];

          /* Set up network driver buffer */

          priv->dev.d_len = len;
          priv->dev.d_buf = rxbuf;

          if (len > 0)
            {
#ifdef CONFIG_NET_PKT
              /* Feed frame into packet tap */

              pkt_input(&priv->dev);
#endif
              /* Route based on Ethertype */

#ifdef CONFIG_NET_IPv4
              if (BUF->type == HTONS(ETHTYPE_IP))
                {
                  ninfo("IPv4 frame\n");
                  ipv4_input(&priv->dev);
                }
              else
#endif
#ifdef CONFIG_NET_IPv6
              if (BUF->type == HTONS(ETHTYPE_IP6))
                {
                  ninfo("IPv6 frame\n");
                  ipv6_input(&priv->dev);
                }
              else
#endif
#ifdef CONFIG_NET_ARP
              if (BUF->type == HTONS(ETHTYPE_ARP))
                {
                  ninfo("ARP frame\n");
                  arp_arpin(&priv->dev);
                }
              else
#endif
                {
                  ninfo("Dropped, Unknown type: %04x\n", BUF->type);
                }
            }
        }
      else
        {
          nwarn("Unexpected descriptor type: 0x%08lx\n",
                (unsigned long)desc_type);
        }

      /* Reset the descriptor for reuse */

      ra_setup_rxdesc(priv, priv->rxhead, rxbuf);

      /* Advance to next descriptor */

      priv->rxhead++;
      if (priv->rxhead >= CONFIG_RA_ETHERNET_NRXDESC)
        {
          priv->rxhead = 0;
        }
    }
}

/****************************************************************************
 * Function: ra_data_interrupt
 *
 * Description:
 *   GWCA data interrupt handler (GWDI).
 *   Handles TX completion and RX frame available events.
 *
 ****************************************************************************/

static int ra_data_interrupt(int irq, void *context, void *arg)
{
  struct ra_ether_s *priv = (struct ra_ether_s *)arg;

  /* GWCA has two interrupt status registers:
   * - GWDIS0 for descriptor queues 0-31 (TX queue 0)
   * - GWDIS1 for descriptor queues 32-63 (RX queue 32)
   */

  uint32_t status0 = getreg32(R_GWCA_GWDIS0);
  uint32_t status1 = getreg32(R_GWCA_GWDIS1);

  /* Clear interrupt status by writing 1 to handled bits */

  if (status0)
    {
      putreg32(status0, R_GWCA_GWDIS0);
    }

  if (status1)
    {
      putreg32(status1, R_GWCA_GWDIS1);
    }

  /* Handle RX interrupt - RX queue 32 is bit 0 in GWDIS1 */

  if (status1 & (1 << (RA_GWCA_RX_QUEUE - 32)))
    {
      ra_receive(priv);
    }

  /* Handle TX completion - TX queue 0 is bit 0 in GWDIS0
   * Reclaim TX descriptors that have been sent.
   */

  if (status0 & (1 << RA_GWCA_TX_QUEUE))
    {
      /* TX descriptors transition to FEMPTY when transmission completes.
       * Poll for more data to send.
       */

      devif_poll(&priv->dev, ra_txpoll);
    }

  return OK;
}

/****************************************************************************
 * Function: ra_phy_interrupt
 *
 * Description:
 *   RMAC PHY interrupt handler (RMPI).
 *   Handles link status changes.
 *
 ****************************************************************************/

static int ra_phy_interrupt(int irq, void *context, void *arg)
{
  struct ra_ether_s *priv = (struct ra_ether_s *)arg;
  uintptr_t base;
  uint32_t status;

  base = R_RMAC_BASE + (priv->port * R_RMAC_CH_STRIDE);

  /* Read RMAC monitoring interrupt status (MMIS0) */

  status = getreg32(base + R_RMAC_MMIS0_OFFSET);

  /* Clear interrupt by writing to disable register then re-enable */

  putreg32(status, base + R_RMAC_MMID0_OFFSET);

  /* TODO: Handle link status change
   * - Read PHY status via MDIO
   * - Update speed/duplex settings in RMAC
   * - Notify network stack of link change
   */

  ninfo("PHY interrupt: status=0x%08lx\n", (unsigned long)status);

  return OK;
}

/****************************************************************************
 * Function: ra_ifup
 *
 * Description:
 *   NuttX Callback: Bring up the Ethernet interface when an IP address is
 *   provided. Completes initialization and transitions to OPERATION mode.
 *
 ****************************************************************************/

static int ra_ifup(struct net_driver_s *dev)
{
  struct ra_ether_s *priv = (struct ra_ether_s *)dev->d_private;
  int ret;

  ninfo("Bringing up eth%d\n", priv->port);

  /* Initialize descriptors */

  ra_init_descriptors(priv);

  /* Transition GWCA to OPERATION mode */

  ret = ra_gwca_set_mode(RA_ETHER_OPC_OPERATION);
  if (ret < 0)
    {
      nerr("Failed to set GWCA to OPERATION mode\n");
      return ret;
    }

  /* Transition ETHA to OPERATION mode */

  ret = ra_etha_set_mode(priv->port, RA_ETHER_OPC_OPERATION);
  if (ret < 0)
    {
      nerr("Failed to set ETHA[%d] to OPERATION mode\n", priv->port);
      return ret;
    }

  /* Enable GWCA interrupts
   * - GWDIE0 for TX queue 0 (bit 0)
   * - GWDIE1 for RX queue 32 (bit 0 in the second register)
   */

  putreg32((1 << RA_GWCA_TX_QUEUE), R_GWCA_GWDIE0);
  putreg32((1 << (RA_GWCA_RX_QUEUE - 32)), R_GWCA_GWDIE1);

  /* Enable RMAC interrupts for link status (if needed) */

  /* TODO: Configure RMAC interrupt mask register */

  priv->bifup = true;
  priv->state = RA_ETHER_STATE_RUNNING;

  ninfo("eth%d is up\n", priv->port);
  return OK;
}

/****************************************************************************
 * Function: ra_ifdown
 *
 * Description:
 *   NuttX Callback: Stop the interface.
 *   Transitions ETHA back to CONFIG mode.
 *
 ****************************************************************************/

static int ra_ifdown(struct net_driver_s *dev)
{
  struct ra_ether_s *priv = (struct ra_ether_s *)dev->d_private;
  int ret;

  ninfo("Bringing down eth%d\n", priv->port);

  /* Disable GWCA interrupts for this port's queues */

  /* Clear interrupt enable bits */

  putreg32(0, R_GWCA_GWDIE0);

  /* Transition ETHA back to CONFIG mode */

  ret = ra_etha_set_mode(priv->port, RA_ETHER_OPC_CONFIG);
  if (ret < 0)
    {
      nwarn("Failed to set ETHA[%d] to CONFIG mode: %d\n", priv->port, ret);
    }

  /* Note: We leave GWCA in OPERATION mode if other ports may be using it.
   * Only transition GWCA to CONFIG if all ports are down.
   */

  priv->bifup = false;
  priv->state = RA_ETHER_STATE_READY;

  ninfo("eth%d is down\n", priv->port);
  return OK;
}

/****************************************************************************
 * Function: ra_txavail
 *
 * Description:
 *   Driver callback invoked when new TX data is available.  This is a
 *   stimulus perform an out-of-cycle poll and, thereby, reduce the TX
 *   latency.
 *
 ****************************************************************************/

static int ra_txavail(struct net_driver_s *dev)
{
  struct ra_ether_s *priv = (struct ra_ether_s *)dev->d_private;

  if (priv->bifup)
    {
      devif_poll(&priv->dev, ra_txpoll);
    }

  return OK;
}

/****************************************************************************
 * Function: ra_ioctl
 *
 * Description:
 *   PHY ioctl
 *
 ****************************************************************************/

#ifdef CONFIG_NETDEV_IOCTL
static int ra_ioctl(struct net_driver_s *dev, int cmd, unsigned long arg)
{
  /* TODO: Implement PHY IOCTLs */

  return -ENOTTY;
}
#endif

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: ra_phy_read
 *
 * Description:
 *   Read a PHY register via MDIO/MDC using RMAC MPSM register.
 *
 ****************************************************************************/

int ra_phy_read(int port, uint8_t phyaddr, uint8_t regaddr, uint16_t *data)
{
  uintptr_t mpsm_addr;
  uint32_t regval;
  int ret;

  if (port >= RA_ETHER_MAX_PORTS || data == NULL)
    {
      return -EINVAL;
    }

  mpsm_addr = R_RMAC_BASE + (port * R_RMAC_CH_STRIDE) + R_RMAC_MPSM_OFFSET;

  /* Wait for any previous operation to complete */

  ret = ra_phy_wait_ready(port);
  if (ret < 0)
    {
      return ret;
    }

  /* Set up MPSM for read operation:
   * PSME = 1 (enable)
   * PSMCS = 2 (read operation)
   * PSMAD = phyaddr
   * PRA = regaddr
   */

  regval = R_RMAC_MPSM_PSME |
           RMAC_MPSM_PSMCS_READ |
           ((uint32_t)phyaddr << RMAC_MPSM_PSMAD_SHIFT) |
           ((uint32_t)regaddr << RMAC_MPSM_PRA_SHIFT);

  putreg32(regval, mpsm_addr);

  /* Wait for operation to complete */

  ret = ra_phy_wait_ready(port);
  if (ret < 0)
    {
      return ret;
    }

  /* Read data from MPSM.PRD field */

  regval = getreg32(mpsm_addr);
  *data = (regval & RMAC_MPSM_PRD_MASK) >> RMAC_MPSM_PRD_SHIFT;

  return OK;
}

/****************************************************************************
 * Name: ra_phy_write
 *
 * Description:
 *   Write a PHY register via MDIO/MDC using RMAC MPSM register.
 *
 ****************************************************************************/

int ra_phy_write(int port, uint8_t phyaddr, uint8_t regaddr, uint16_t data)
{
  uintptr_t mpsm_addr;
  uint32_t regval;
  int ret;

  if (port >= RA_ETHER_MAX_PORTS)
    {
      return -EINVAL;
    }

  mpsm_addr = R_RMAC_BASE + (port * R_RMAC_CH_STRIDE) + R_RMAC_MPSM_OFFSET;

  /* Wait for any previous operation to complete */

  ret = ra_phy_wait_ready(port);
  if (ret < 0)
    {
      return ret;
    }

  /* Set up MPSM for write operation:
   * PSME = 1 (enable)
   * PSMCS = 1 (write operation)
   * PSMAD = phyaddr
   * PRA = regaddr
   * PRD = data
   */

  regval = R_RMAC_MPSM_PSME |
           RMAC_MPSM_PSMCS_WRITE |
           ((uint32_t)phyaddr << RMAC_MPSM_PSMAD_SHIFT) |
           ((uint32_t)regaddr << RMAC_MPSM_PRA_SHIFT) |
           ((uint32_t)data << RMAC_MPSM_PRD_SHIFT);

  putreg32(regval, mpsm_addr);

  /* Wait for operation to complete */

  ret = ra_phy_wait_ready(port);

  return ret;
}

/****************************************************************************
 * Name: ra_ether_set_macaddr
 *
 * Description:
 *   Set the MAC address for the specified Ethernet port.
 *
 ****************************************************************************/

int ra_ether_set_macaddr(int port, const uint8_t *mac)
{
  uintptr_t base;

  if (port >= RA_ETHER_MAX_PORTS || mac == NULL)
    {
      return -EINVAL;
    }

  base = R_RMAC_BASE + (port * R_RMAC_CH_STRIDE);

  /* Set MAC address registers */

  putreg32((mac[2] << 24) | (mac[3] << 16) | (mac[4] << 8) | mac[5],
           base + R_RMAC_MRMAC0_OFFSET);
  putreg32((mac[0] << 8) | mac[1],
           base + R_RMAC_MRMAC1_OFFSET);

  return OK;
}

/****************************************************************************
 * Name: ra_ether_get_macaddr
 *
 * Description:
 *   Get the MAC address for the specified Ethernet port.
 *
 ****************************************************************************/

int ra_ether_get_macaddr(int port, uint8_t *mac)
{
  uintptr_t base;
  uint32_t mac0, mac1;

  if (port >= RA_ETHER_MAX_PORTS || mac == NULL)
    {
      return -EINVAL;
    }

  base = R_RMAC_BASE + (port * R_RMAC_CH_STRIDE);

  /* Read MAC address registers */

  mac0 = getreg32(base + R_RMAC_MRMAC0_OFFSET);
  mac1 = getreg32(base + R_RMAC_MRMAC1_OFFSET);

  mac[0] = (mac1 >> 8) & 0xFF;
  mac[1] = mac1 & 0xFF;
  mac[2] = (mac0 >> 24) & 0xFF;
  mac[3] = (mac0 >> 16) & 0xFF;
  mac[4] = (mac0 >> 8) & 0xFF;
  mac[5] = mac0 & 0xFF;

  return OK;
}

/****************************************************************************
 * Function: ra_ether_initialize
 *
 * Description:
 *   Initialize the Ethernet driver for the specified port.
 *   This initializes the Layer 3 Ethernet Switch components:
 *   COMA, GWCA, ETHA, and RMAC.
 *
 ****************************************************************************/

int ra_ether_initialize(int port)
{
  struct ra_ether_s *priv;
  int ret;

  ninfo("Initializing Ethernet port %d\n", port);

  /* Validate port number */

  if (port >= CONFIG_RA_ETHERNET_NINTERFACES || port >= RA_ETHER_MAX_PORTS)
    {
      nerr("Invalid port number: %d\n", port);
      return -EINVAL;
    }

  priv = &g_ra_ether[port];

  /* Initialize the driver structure */

  memset(priv, 0, sizeof(struct ra_ether_s));
  priv->port = port;
  priv->state = RA_ETHER_STATE_UNINIT;

  /* Set up NuttX network driver interface */

  priv->dev.d_ifup    = ra_ifup;
  priv->dev.d_ifdown  = ra_ifdown;
  priv->dev.d_txavail = ra_txavail;
#ifdef CONFIG_NETDEV_IOCTL
  priv->dev.d_ioctl   = ra_ioctl;
#endif
  priv->dev.d_private = priv;

  /* Assign descriptor and buffer pointers (per-interface) */

  priv->txdesc   = g_txdesc[port];
  priv->rxdesc   = g_rxdesc[port];
  priv->txlink   = &g_txlink[port];  /* DTCM-located link descriptor */
  priv->rxlink   = &g_rxlink[port];  /* DTCM-located link descriptor */
  priv->txbuffer = g_txbuffer[port];
  priv->rxbuffer = g_rxbuffer[port];

  /* Set default configuration */

  priv->phy_mode = RA_ETHER_PHY_RMII;    /* Default to RMII */
  priv->speed    = RA_ETHER_SPEED_100M;  /* Default to 100 Mbps */
  priv->duplex   = RA_ETHER_DUPLEX_FULL; /* Default to full duplex */
  priv->phyaddr  = 0;                    /* Default PHY address */

  /* Set default MAC address (should be overridden by board config) */

  priv->mac[0] = 0x02;  /* Locally administered */
  priv->mac[1] = 0x00;
  priv->mac[2] = 0x00;
  priv->mac[3] = 0x00;
  priv->mac[4] = 0x00;
  priv->mac[5] = port + 1;

  /* Step 1: Initialize shared Layer 3 Switch resources (COMA, GWCA)
   * This is done once for the first port initialization.
   */

  ret = ra_l3switch_init();
  if (ret < 0)
    {
      nerr("Layer 3 Switch initialization failed: %d\n", ret);
      return ret;
    }

  /* Step 2: Initialize ETHA for this port */

  ret = ra_etha_init(port);
  if (ret < 0)
    {
      nerr("ETHA[%d] initialization failed: %d\n", port, ret);
      return ret;
    }

  /* Step 3: Initialize RMAC for this port */

  ret = ra_rmac_init(priv);
  if (ret < 0)
    {
      nerr("RMAC[%d] initialization failed: %d\n", port, ret);
      return ret;
    }

  /* Step 4: Attach GWCA data interrupt (shared across ports)
   * Use GWDI0 for primary data interrupt handling
   */

  priv->irq_data = ra_icu_attach(RA_ELC_ETHER_GWDI0, ra_data_interrupt,
                                  priv, true);
  if (priv->irq_data < 0)
    {
      nerr("Failed to attach GWCA data interrupt: %d\n", priv->irq_data);
      return priv->irq_data;
    }

  /* Step 5: Attach RMAC PHY interrupt (optional, for link status)
   * Use port-specific RMPI: RMPI0 for port 0, RMPI1 for port 1
   */

  priv->irq_phy = ra_icu_attach(
      (port == 0) ? RA_ELC_ETHER_RMPI0 : RA_ELC_ETHER_RMPI1,
      ra_phy_interrupt, priv, true);
  if (priv->irq_phy < 0)
    {
      nwarn("Failed to attach RMAC PHY interrupt: %d (continuing)\n",
            priv->irq_phy);
      priv->irq_phy = -1;  /* Mark as not attached */
    }

  priv->state = RA_ETHER_STATE_READY;

  /* Step 6: Register the device with the OS */

  ret = netdev_register(&priv->dev, NET_LL_ETHERNET);
  if (ret < 0)
    {
      nerr("netdev_register failed: %d\n", ret);
      return ret;
    }

  ninfo("Ethernet port %d initialized successfully\n", port);
  return OK;
}

#endif /* CONFIG_RA_ETHERNET */
