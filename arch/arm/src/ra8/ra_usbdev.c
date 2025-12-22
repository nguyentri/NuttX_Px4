/****************************************************************************
 * arch/arm/src/ra8/ra_usbdev.c
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
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>

#include <sys/types.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <errno.h>
#include <debug.h>

#include <nuttx/arch.h>
#include <nuttx/kmalloc.h>
#include <nuttx/usb/usb.h>
#include <nuttx/usb/usbdev.h>
#include <nuttx/usb/usbdev_trace.h>

#include <arch/board/board.h>

#include "chip.h"
#include "arm_internal.h"
#include "hardware/ra_memorymap.h"
#include "hardware/ra8p1/ra_usbfs.h"
#include "ra_mstp.h"
#include "ra_icu.h"
#include "ra_gpio.h"
#include "ra8_usbdev.h"

#ifdef CONFIG_RA_USBDEV

/****************************************************************************
 * Private Data
 ****************************************************************************/

/* Global USB device controller state */

static struct ra_usbdev_s g_usbdev;

/* Endpoint operations table */

static const struct usbdev_epops_s g_epops =
{
  .configure   = ra_epconfigure,
  .disable     = ra_epdisable,
  .allocreq    = ra_epallocreq,
  .freereq     = ra_epfreereq,
  .submit      = ra_epsubmit,
  .cancel      = ra_epcancel,
  .stall       = ra_epstall,
};

/* Device operations table */

static const struct usbdev_ops_s g_devops =
{
  .allocep     = ra_allocep,
  .freeep      = ra_freeep,
  .getframe    = ra_getframe,
  .wakeup      = ra_wakeup,
  .selfpowered = ra_selfpowered,
  .pullup      = ra_pullup,
};

/****************************************************************************
 * Private Functions
 ****************************************************************************/

/****************************************************************************
 * Name: ra_rqdequeue
 *
 * Description:
 *   Remove a request from an endpoint request queue
 *
 ****************************************************************************/

static struct ra_req_s *ra_rqdequeue(struct ra_ep_s *privep)
{
  struct ra_req_s *ret = privep->head;

  if (ret)
    {
      privep->head = ret->flink;
      if (!privep->head)
        {
          privep->tail = NULL;
        }

      ret->flink = NULL;
    }

  return ret;
}

/****************************************************************************
 * Name: ra_rqenqueue
 *
 * Description:
 *   Add a request to an endpoint request queue
 *
 ****************************************************************************/

static bool ra_rqenqueue(struct ra_ep_s *privep, struct ra_req_s *req)
{
  bool is_empty = !privep->head;

  req->flink = NULL;
  if (is_empty)
    {
      privep->head = req;
      privep->tail = req;
    }
  else
    {
      privep->tail->flink = req;
      privep->tail        = req;
    }

  return is_empty;
}

/****************************************************************************
 * Name: ra_fifo_write
 *
 * Description:
 *   Write data to USB FIFO using CPU (PIO mode) or DMA
 *
 ****************************************************************************/

static void ra_fifo_write(uint8_t pipe, const uint8_t *data, size_t len)
{
  uint16_t fifosel;

#ifdef CONFIG_RA_USBDEV_DMA
  /* Use DMA for bulk transfers on pipes 1-2 if data is large enough */

  if ((pipe == 1 || pipe == 2) && len >= 64)
    {
      /* Select D0/D1 FIFO for DMA transfer */

      uint32_t fifo_addr = (pipe == 1) ? R_USBFS_D0FIFO : R_USBFS_D1FIFO;
      uint16_t fifosel_reg = (pipe == 1) ? R_USBFS_D0FIFOSEL : R_USBFS_D1FIFOSEL;

      /* Select pipe for D0/D1 FIFO access */

      fifosel = (pipe & R_USBFS_D0FIFOSEL_CURPIPE_MASK);
      fifosel |= R_USBFS_D0FIFOSEL_MBW_16BIT;  /* 16-bit access */
      putreg16(fifosel, fifosel_reg);

      /* Wait for FIFO ready */

      uint16_t fifoctr_reg = (pipe == 1) ? R_USBFS_D0FIFOCTR : R_USBFS_D1FIFOCTR;
      while (!(getreg16(fifoctr_reg) & R_USBFS_D0FIFOCTR_FRDY))
        {
          /* Busy wait */
        }

      /* Configure and start DMA transfer */
      /* TODO: Implement DMAC configuration for USB transfers */
      /* For now, fall through to PIO mode */
    }
#endif

  /* Use PIO mode for control transfers or when DMA not available */

  /* Select pipe for CFIFO access */

  fifosel = (pipe & R_USBFS_CFIFOSEL_CURPIPE_MASK);
  if (pipe == 0)  /* DCP uses ISEL for direction */
    {
      fifosel |= R_USBFS_CFIFOSEL_ISEL;  /* IN direction */
    }

  putreg16(fifosel, R_USBFS_CFIFOSEL);

  /* Wait for FIFO ready */

  while (!(getreg16(R_USBFS_CFIFOCTR) & R_USBFS_CFIFOCTR_FRDY))
    {
      /* Busy wait */
    }

  /* Write data to FIFO */

  while (len > 0)
    {
      putreg8(*data++, R_USBFS_CFIFO);
      len--;
    }

  /* Set buffer valid flag */

  modifyreg16(R_USBFS_CFIFOCTR, 0, R_USBFS_CFIFOCTR_BVAL);
}

/****************************************************************************
 * Name: ra_fifo_read
 *
 * Description:
 *   Read data from USB FIFO using CPU (PIO mode) or DMA
 *
 ****************************************************************************/

static size_t ra_fifo_read(uint8_t pipe, uint8_t *data, size_t maxlen)
{
  uint16_t fifosel;
  uint16_t fifoctr;
  size_t len;

#ifdef CONFIG_RA_USBDEV_DMA
  /* Use DMA for bulk transfers on pipes 1-2 if buffer is large enough */

  if ((pipe == 1 || pipe == 2) && maxlen >= 64)
    {
      /* Select D0/D1 FIFO for DMA transfer */

      uint16_t fifosel_reg = (pipe == 1) ? R_USBFS_D0FIFOSEL : R_USBFS_D1FIFOSEL;
      uint16_t fifoctr_reg = (pipe == 1) ? R_USBFS_D0FIFOCTR : R_USBFS_D1FIFOCTR;

      /* Select pipe for D0/D1 FIFO access */

      fifosel = (pipe & R_USBFS_D0FIFOSEL_CURPIPE_MASK);
      fifosel |= R_USBFS_D0FIFOSEL_MBW_16BIT;  /* 16-bit access */
      putreg16(fifosel, fifosel_reg);

      /* Wait for FIFO ready */

      while (!(getreg16(fifoctr_reg) & R_USBFS_D0FIFOCTR_FRDY))
        {
          /* Busy wait */
        }

      /* Get received data length */

      fifoctr = getreg16(fifoctr_reg);
      len = fifoctr & R_USBFS_D0FIFOCTR_DTLN_MASK;

      /* Configure and start DMA transfer */
      /* TODO: Implement DMAC configuration for USB transfers */
      /* For now, fall through to PIO mode */
    }
#endif

  /* Use PIO mode for control transfers or when DMA not available */

  /* Select pipe for CFIFO access */

  fifosel = (pipe & R_USBFS_CFIFOSEL_CURPIPE_MASK);
  putreg16(fifosel, R_USBFS_CFIFOSEL);

  /* Wait for FIFO ready */

  while (!(getreg16(R_USBFS_CFIFOCTR) & R_USBFS_CFIFOCTR_FRDY))
    {
      /* Busy wait */
    }

  /* Get received data length */

  fifoctr = getreg16(R_USBFS_CFIFOCTR);
  len = fifoctr & R_USBFS_CFIFOCTR_DTLN_MASK;

  if (len > maxlen)
    {
      len = maxlen;
    }

  /* Read data from FIFO */

  for (size_t i = 0; i < len; i++)
    {
      data[i] = getreg8(R_USBFS_CFIFO);
    }

  /* Clear buffer */

  modifyreg16(R_USBFS_CFIFOCTR, 0, R_USBFS_CFIFOCTR_BCLR);

  return len;
}

/****************************************************************************
 * Name: ra_reqcomplete
 *
 * Description:
 *   Complete a request and call the completion callback
 *
 ****************************************************************************/

static void ra_reqcomplete(struct ra_ep_s *privep,
                          struct ra_req_s *privreq, int16_t result)
{
  /* Save the result in the request structure */

  privreq->req.result = result;

  /* Callback to the request completion handler */

  privreq->req.callback(&privep->ep, &privreq->req);
}

/****************************************************************************
 * Name: ra_cancelrequests
 *
 * Description:
 *   Cancel all pending requests for an endpoint
 *
 ****************************************************************************/

static void ra_cancelrequests(struct ra_ep_s *privep, int16_t status)
{
  while (privep->head != NULL)
    {
      usbtrace(TRACE_COMPLETE(privep->epphy),
               (privep->head)->req.xfrd);
      ra_reqcomplete(privep, ra_rqdequeue(privep), status);
    }
}

/****************************************************************************
 * Name: ra_epfindbyaddr
 *
 * Description:
 *   Find the physical endpoint structure corresponding to a logical
 *   endpoint address
 *
 ****************************************************************************/

static struct ra_ep_s *ra_epfindbyaddr(struct ra_usbdev_s *priv,
                                       uint16_t eplog)
{
  struct ra_ep_s *privep;
  int i;

  /* Endpoint zero is a special case */

  if (USB_EPNO(eplog) == 0)
    {
      return &priv->eplist[0];
    }

  /* Handle the remaining endpoints */

  for (i = 1; i < RA_NPHYSENDPOINTS; i++)
    {
      privep = &priv->eplist[i];

      /* Same logical endpoint number? (includes direction bit) */

      if (eplog == privep->eplog)
        {
          return privep;
        }
    }

  return NULL;
}

/****************************************************************************
 * Name: ra_dispatchrequest
 *
 * Description:
 *   Provide unhandled setup actions to the class driver
 *
 ****************************************************************************/

static void ra_dispatchrequest(struct ra_usbdev_s *priv,
                               const struct usb_ctrlreq_s *ctrl)
{
  int ret = -EIO;

  usbtrace(TRACE_INTDECODE(RA_TRACEINTID_DISPATCH), 0);

  if (priv->driver)
    {
      /* Forward to the control request to the class driver implementation */

      ret = CLASS_SETUP(priv->driver, &priv->usbdev, ctrl, priv->ep0buf,
                        priv->ep0buf_len);
    }

  if (ret < 0)
    {
      /* Stall on failure */

      usbtrace(TRACE_DEVERROR(RA_TRACEERR_DISPATCHSTALL), 0);

      /* Stall EP0 */

      modifyreg16(R_USBFS_DCPCTR, 0,
                  (1 << 14));  /* PIDSTALL bit */
    }
}

/****************************************************************************
 * Name: ra_ep0configure
 *
 * Description:
 *   Configure endpoint 0 (default control pipe)
 *
 ****************************************************************************/

static void ra_ep0configure(struct ra_usbdev_s *priv)
{
  /* Configure DCP max packet size */

  putreg16(RA_EP0_MAXPACKET, R_USBFS_DCPMAXP);

  uinfo("EP0 configured: maxpacket=%d\n", RA_EP0_MAXPACKET);
}

/****************************************************************************
 * Name: ra_usbreset
 *
 * Description:
 *   Handle USB bus reset
 *
 ****************************************************************************/

static void ra_usbreset(struct ra_usbdev_s *priv)
{
  int i;

  uinfo("USB Reset\n");

  /* Cancel all transfers */

  for (i = 0; i < RA_NPHYSENDPOINTS; i++)
    {
      struct ra_ep_s *privep = &priv->eplist[i];
      ra_cancelrequests(privep, -ESHUTDOWN);
      privep->stalled = false;
    }

  /* Reset device state */

  priv->paddr = 0;
  priv->paddrset = false;
  priv->configured = false;
  priv->ep0state = EP0STATE_IDLE;

  /* Tell the class driver that we are disconnected */

  if (priv->driver)
    {
      CLASS_DISCONNECT(priv->driver, &priv->usbdev);
    }

  /* Configure EP0 */

  ra_ep0configure(priv);
}

/****************************************************************************
 * Name: ra_ep0setup
 *
 * Description:
 *   Handle EP0 setup request
 *
 ****************************************************************************/

static void ra_ep0setup(struct ra_usbdev_s *priv)
{
  struct usb_ctrlreq_s *ctrl = &priv->ep0ctrl;
  uint16_t value;
  uint16_t index;
  uint16_t len;

  /* Read setup packet from USBREQ registers */

  ctrl->type = getreg16(R_USBFS_USBREQ);
  ctrl->req = (ctrl->type >> 8) & 0xff;
  ctrl->type = ctrl->type & 0xff;

  value = getreg16(R_USBFS_USBVAL);
  ctrl->value[0] = value & 0xff;
  ctrl->value[1] = (value >> 8) & 0xff;

  index = getreg16(R_USBFS_USBINDX);
  ctrl->index[0] = index & 0xff;
  ctrl->index[1] = (index >> 8) & 0xff;

  len = getreg16(R_USBFS_USBLENG);
  ctrl->len[0] = len & 0xff;
  ctrl->len[1] = (len >> 8) & 0xff;

  uinfo("SETUP: type=%02x req=%02x value=%04x index=%04x len=%04x\n",
        ctrl->type, ctrl->req, value, index, len);

  /* Dispatch to the class driver */

  priv->ep0buf_len = 0;
  ra_dispatchrequest(priv, ctrl);
}

/****************************************************************************
 * Name: ra_handle_brdy
 *
 * Description:
 *   Handle buffer ready (BRDY) interrupt - data received on OUT endpoint
 *
 ****************************************************************************/

static void ra_handle_brdy(struct ra_usbdev_s *priv, uint16_t brdysts)
{
  int pipe;

  /* Check each pipe */

  for (pipe = 1; pipe < RA_NLOGENDPOINTS; pipe++)
    {
      if (brdysts & (1 << pipe))
        {
          struct ra_ep_s *privep;
          struct ra_req_s *privreq;

          /* Find endpoint for this pipe */

          privep = &priv->eplist[pipe * 2];  /* OUT endpoint */

          /* Get current request */

          privreq = privep->head;
          if (privreq)
            {
              uint8_t *dest = privreq->req.buf + privreq->req.xfrd;
              size_t remaining = privreq->req.len - privreq->req.xfrd;
              size_t bytesread;

              /* Read from FIFO */

              bytesread = ra_fifo_read(pipe, dest, remaining);
              privreq->req.xfrd += bytesread;

              /* Check if transfer complete */

              if (privreq->req.xfrd >= privreq->req.len ||
                  bytesread < privep->ep.maxpacket)
                {
                  /* Complete the request */

                  usbtrace(TRACE_INTDECODE(RA_TRACEINTID_EPIN), pipe);
                  ra_rqdequeue(privep);
                  ra_reqcomplete(privep, privreq, OK);

                  /* Start next request if any */

                  privreq = privep->head;
                  if (privreq)
                    {
                      /* Enable BRDY for next transfer */

                      modifyreg16(R_USBFS_BRDYENB, 0, (1 << pipe));
                    }
                }
            }

          /* Clear interrupt */

          putreg16(~(1 << pipe), R_USBFS_BRDYSTS);
        }
    }
}

/****************************************************************************
 * Name: ra_handle_bemp
 *
 * Description:
 *   Handle buffer empty (BEMP) interrupt - data sent on IN endpoint
 *
 ****************************************************************************/

static void ra_handle_bemp(struct ra_usbdev_s *priv, uint16_t bempsts)
{
  int pipe;

  /* Check each pipe */

  for (pipe = 1; pipe < RA_NLOGENDPOINTS; pipe++)
    {
      if (bempsts & (1 << pipe))
        {
          struct ra_ep_s *privep;
          struct ra_req_s *privreq;

          /* Find endpoint for this pipe */

          privep = &priv->eplist[pipe * 2 + 1];  /* IN endpoint */

          /* Get current request */

          privreq = privep->head;
          if (privreq)
            {
              /* Check if more data to send */

              if (privreq->req.xfrd < privreq->req.len)
                {
                  uint8_t *src = privreq->req.buf + privreq->req.xfrd;
                  size_t remaining = privreq->req.len - privreq->req.xfrd;
                  size_t to_write = remaining;

                  if (to_write > privep->ep.maxpacket)
                    {
                      to_write = privep->ep.maxpacket;
                    }

                  /* Write to FIFO */

                  ra_fifo_write(pipe, src, to_write);
                  privreq->req.xfrd += to_write;
                }
              else
                {
                  /* Transfer complete */

                  usbtrace(TRACE_INTDECODE(RA_TRACEINTID_EPOUT), pipe);
                  ra_rqdequeue(privep);
                  ra_reqcomplete(privep, privreq, OK);

                  /* Disable BEMP interrupt for this pipe */

                  modifyreg16(R_USBFS_BEMPENB, (1 << pipe), 0);

                  /* Start next request if any */

                  privreq = privep->head;
                  if (privreq && privreq->req.len > 0)
                    {
                      uint8_t *src = privreq->req.buf;
                      size_t to_write = privreq->req.len;

                      if (to_write > privep->ep.maxpacket)
                        {
                          to_write = privep->ep.maxpacket;
                        }

                      ra_fifo_write(pipe, src, to_write);
                      privreq->req.xfrd = to_write;

                      /* Enable BEMP interrupt */

                      modifyreg16(R_USBFS_BEMPENB, 0, (1 << pipe));
                    }
                }
            }

          /* Clear interrupt */

          putreg16(~(1 << pipe), R_USBFS_BEMPSTS);
        }
    }
}

/****************************************************************************
 * Name: ra_usbfs_interrupt
 *
 * Description:
 *   Main USB interrupt handler
 *
 ****************************************************************************/

static int ra_usbfs_interrupt(int irq, void *context, void *arg)
{
  struct ra_usbdev_s *priv = (struct ra_usbdev_s *)arg;
  uint16_t intsts0;
  uint16_t intsts1;
  uint16_t brdysts;
  uint16_t bempsts;
  uint16_t dvsq;

  /* Read interrupt status registers */

  intsts0 = getreg16(R_USBFS_INTSTS0);
  intsts1 = getreg16(R_USBFS_INTSTS1);
  brdysts = getreg16(R_USBFS_BRDYSTS);
  bempsts = getreg16(R_USBFS_BEMPSTS);

  usbtrace(TRACE_INTENTRY(RA_TRACEINTID_USB), intsts0);

  /* Handle buffer ready (data received) */

  if (brdysts)
    {
      ra_handle_brdy(priv, brdysts);
    }

  /* Handle buffer empty (data sent) */

  if (bempsts)
    {
      ra_handle_bemp(priv, bempsts);
    }

  /* Handle VBUS status change */

  if (intsts0 & (1 << 15))  /* VBINT */
    {
      uinfo("VBUS interrupt\n");

      /* Check VBUS status */

      if (intsts0 & (1 << 7))  /* VBSTS */
        {
          priv->attached = true;
          uinfo("VBUS ON - attached\n");
        }
      else
        {
          priv->attached = false;
          uinfo("VBUS OFF - detached\n");
        }

      /* Clear interrupt */

      putreg16(intsts0 & ~(1 << 15), R_USBFS_INTSTS0);
    }

  /* Handle device state change */

  if (intsts0 & (1 << 12))  /* DVST */
    {
      dvsq = (intsts0 >> 4) & 0x7;

      uinfo("Device state change: DVSQ=%d\n", dvsq);

      switch (dvsq)
        {
          case 0:  /* Powered state */
            uinfo("State: Powered\n");
            ra_usbreset(priv);
            break;

          case 1:  /* Default state (after reset) */
            uinfo("State: Default\n");
            usbtrace(TRACE_INTDECODE(RA_TRACEINTID_DEVRESET), 0);
            ra_usbreset(priv);
            break;

          case 2:  /* Address state */
            uinfo("State: Address\n");
            break;

          case 3:  /* Configured state */
            uinfo("State: Configured\n");
            priv->configured = true;
            break;

          default:
            break;
        }

      /* Clear interrupt */

      putreg16(intsts0 & ~(1 << 12), R_USBFS_INTSTS0);
    }

  /* Handle control transfer stage transition */

  if (intsts0 & (1 << 11))  /* CTRT */
    {
      uint16_t ctsq = intsts0 & 0x7;

      uinfo("Control transfer: CTSQ=%d\n", ctsq);

      switch (ctsq)
        {
          case 0:  /* Idle or setup stage */
            usbtrace(TRACE_INTDECODE(RA_TRACEINTID_EP0SETUP), 0);
            ra_ep0setup(priv);
            priv->ep0state = EP0STATE_SETUP_OUT;
            break;

          case 2:  /* Control read status stage */
            priv->ep0state = EP0STATE_STATUS_OUT;
            break;

          case 4:  /* Control write status stage */
            priv->ep0state = EP0STATE_STATUS_IN;
            break;

          case 5:  /* Control (no data) status stage */
            priv->ep0state = EP0STATE_STATUS_IN;
            break;

          default:
            break;
        }

      /* Clear interrupt */

      putreg16(intsts0 & ~(1 << 11), R_USBFS_INTSTS0);
    }

  usbtrace(TRACE_INTEXIT(RA_TRACEINTID_USB), 0);

  return OK;
}

/****************************************************************************
 * Name: ra_usbclk_enable
 *
 * Description:
 *   Enable USB clock (48MHz from PLL2R)
 *
 ****************************************************************************/

static int ra_usbclk_enable(void)
{
  /* USB clock is configured in ra_clockconfig() during boot */
  /* PLL2R (480MHz) / 10 = 48MHz for USB */

  /* Enable USB module clock via SCKE bit */

  modifyreg16(R_USBFS_SYSCFG, 0, R_USBFS_SYSCFG_SCKE);

  /* Wait for clock stabilization */

  up_udelay(100);

  return OK;
}

/****************************************************************************
 * Name: ra_usbdev_hwinit
 *
 * Description:
 *   Initialize USB hardware registers
 *
 ****************************************************************************/

static int ra_usbdev_hwinit(struct ra_usbdev_s *priv)
{
  uinfo("Initializing USB hardware\n");

  /* 1. Disable USB module during configuration */

  putreg16(0, R_USBFS_SYSCFG);

  /* 2. Enable USB clock */

  ra_usbclk_enable();

  /* 3. Set device mode (DCFM=0 for peripheral) */

  modifyreg16(R_USBFS_SYSCFG, R_USBFS_SYSCFG_DCFM, 0);

  /* 4. Configure D+ pull-up resistor control (DPRPU=0 initially) */

  modifyreg16(R_USBFS_SYSCFG, R_USBFS_SYSCFG_DPRPU, 0);

  /* 5. Configure default control pipe (DCP) */

  ra_ep0configure(priv);

  /* 6. Clear all interrupt status */

  putreg16(0, R_USBFS_INTSTS0);
  putreg16(0, R_USBFS_INTSTS1);
  putreg16(0, R_USBFS_BRDYSTS);
  putreg16(0, R_USBFS_NRDYSTS);
  putreg16(0, R_USBFS_BEMPSTS);

  /* 7. Enable required interrupts */

  putreg16(R_USBFS_INTENB0_VBSE |    /* VBUS change */
           R_USBFS_INTENB0_RSME |    /* Resume */
           R_USBFS_INTENB0_DVSE |    /* Device state change */
           R_USBFS_INTENB0_CTRE |    /* Control transfer */
           R_USBFS_INTENB0_BEMPE |   /* Buffer empty */
           R_USBFS_INTENB0_BRDYE,    /* Buffer ready */
           R_USBFS_INTENB0);

  /* 8. Enable USB module */

  modifyreg16(R_USBFS_SYSCFG, 0, R_USBFS_SYSCFG_USBE);

  uinfo("USB hardware initialized\n");

  return OK;
}

/****************************************************************************
 * Endpoint Operations
 ****************************************************************************/

static int ra_epconfigure(struct usbdev_ep_s *ep,
                         const struct usb_epdesc_s *desc, bool last)
{
  struct ra_ep_s *privep = (struct ra_ep_s *)ep;
  uint16_t maxpacket;
  uint8_t eptype;
  uint16_t pipecfg;
  uint16_t pipemaxp;
  uint8_t pipe;

  usbtrace(TRACE_EPCONFIGURE, privep->epphy);

  /* Get endpoint parameters */

  maxpacket = GETUINT16(desc->mxpacketsize);
  eptype = desc->attr & USB_EP_ATTR_XFERTYPE_MASK;

  /* Map logical endpoint to physical pipe */

  pipe = privep->epphy / 2;  /* Each logical EP uses one pipe */
  if (pipe == 0 || pipe >= RA_NLOGENDPOINTS)
    {
      usbtrace(TRACE_DEVERROR(RA_TRACEERR_BADEPNO), privep->epphy);
      return -EINVAL;
    }

  uinfo("Configure EP%d: pipe=%d type=%d maxpacket=%d\n",
        privep->epphy, pipe, eptype, maxpacket);

  /* Configure pipe */

  pipecfg = pipe & 0xF;  /* Pipe number */

  /* Set direction */

  if (USB_ISEPIN(privep->eplog))
    {
      pipecfg |= (1 << 4);  /* DIR=1 for IN */
    }

  /* Set endpoint type */

  switch (eptype)
    {
      case USB_EP_ATTR_XFER_BULK:
        pipecfg |= (1 << 14);  /* TYPE=01 (Bulk) */
        break;

      case USB_EP_ATTR_XFER_INT:
        pipecfg |= (2 << 14);  /* TYPE=10 (Interrupt) */
        break;

      case USB_EP_ATTR_XFER_ISOC:
        pipecfg |= (3 << 14);  /* TYPE=11 (Isochronous) */
        break;

      default:
        return -EINVAL;
    }

  /* Write configuration */

  putreg16(0, R_USBFS_PIPESEL);  /* Deselect pipe first */
  putreg16(pipe, R_USBFS_PIPESEL);  /* Select pipe */
  putreg16(pipecfg, R_USBFS_PIPECFG);

  /* Configure max packet size */

  pipemaxp = maxpacket & 0x7FF;  /* MXPS[10:0] */
  putreg16(pipemaxp, R_USBFS_PIPEMAXP);

  /* Enable pipe */

  putreg16((1 << 9), R_USBFS_PIPE1CTR + (pipe - 1) * 2);  /* PID=BUF */

  privep->ep.maxpacket = maxpacket;
  privep->stalled = false;

  return OK;
}

static int ra_epdisable(struct usbdev_ep_s *ep)
{
  struct ra_ep_s *privep = (struct ra_ep_s *)ep;
  uint8_t pipe;
  irqstate_t flags;

  usbtrace(TRACE_EPDISABLE, privep->epphy);

  /* Map to pipe */

  pipe = privep->epphy / 2;
  if (pipe == 0 || pipe >= RA_NLOGENDPOINTS)
    {
      return -EINVAL;
    }

  flags = enter_critical_section();

  /* Disable pipe (set PID=NAK) */

  putreg16(0, R_USBFS_PIPE1CTR + (pipe - 1) * 2);

  /* Cancel any pending requests */

  ra_cancelrequests(privep, -ESHUTDOWN);

  leave_critical_section(flags);

  return OK;
}

static struct usbdev_req_s *ra_epallocreq(struct usbdev_ep_s *ep)
{
  struct ra_req_s *privreq;

  privreq = (struct ra_req_s *)kmm_malloc(sizeof(struct ra_req_s));
  if (!privreq)
    {
      usbtrace(TRACE_DEVERROR(RA_TRACEERR_ALLOCFAIL), 0);
      return NULL;
    }

  memset(privreq, 0, sizeof(struct ra_req_s));
  return &privreq->req;
}

static void ra_epfreereq(struct usbdev_ep_s *ep, struct usbdev_req_s *req)
{
  struct ra_req_s *privreq = (struct ra_req_s *)req;

  if (privreq)
    {
      kmm_free(privreq);
    }
}

static int ra_epsubmit(struct usbdev_ep_s *ep, struct usbdev_req_s *req)
{
  struct ra_req_s *privreq = (struct ra_req_s *)req;
  struct ra_ep_s *privep = (struct ra_ep_s *)ep;
  struct ra_usbdev_s *priv = privep->dev;
  irqstate_t flags;
  uint8_t pipe;
  bool is_empty;

  usbtrace(TRACE_EPSUBMIT, privep->epphy);

  /* Handle EP0 specially */

  if (privep->epphy == 0)
    {
      /* EP0 IN transfer */

      if (req->len > 0)
        {
          ra_fifo_write(0, req->buf, req->len);
          req->xfrd = req->len;
        }

      ra_reqcomplete(privep, privreq, OK);
      return OK;
    }

  /* Get pipe number for data endpoints */

  pipe = privep->epphy / 2;
  if (pipe == 0 || pipe >= RA_NLOGENDPOINTS)
    {
      usbtrace(TRACE_DEVERROR(RA_TRACEERR_BADEPNO), privep->epphy);
      return -EINVAL;
    }

  req->result = -EINPROGRESS;
  req->xfrd = 0;

  flags = enter_critical_section();

  /* Queue the request */

  is_empty = ra_rqenqueue(privep, privreq);

  /* If queue was empty, start transfer immediately */

  if (is_empty)
    {
      if (USB_ISEPIN(privep->eplog))
        {
          /* IN transfer - write to FIFO */

          if (req->len > 0)
            {
              size_t to_write = req->len;
              if (to_write > privep->ep.maxpacket)
                {
                  to_write = privep->ep.maxpacket;
                }

              ra_fifo_write(pipe, req->buf, to_write);
              req->xfrd = to_write;
            }

          /* Enable buffer empty interrupt for this pipe */

          modifyreg16(R_USBFS_BEMPENB, 0, (1 << pipe));
        }
      else
        {
          /* OUT transfer - enable buffer ready interrupt */

          modifyreg16(R_USBFS_BRDYENB, 0, (1 << pipe));
        }
    }

  leave_critical_section(flags);

  return OK;
}

static int ra_epcancel(struct usbdev_ep_s *ep, struct usbdev_req_s *req)
{
  struct ra_ep_s *privep = (struct ra_ep_s *)ep;
  irqstate_t flags;

  flags = enter_critical_section();
  ra_cancelrequests(privep, -ESHUTDOWN);
  leave_critical_section(flags);

  return OK;
}

static int ra_epstall(struct usbdev_ep_s *ep, bool resume)
{
  struct ra_ep_s *privep = (struct ra_ep_s *)ep;
  uint8_t pipe;
  irqstate_t flags;

  usbtrace(resume ? TRACE_EPRESUME : TRACE_EPSTALL, privep->epphy);

  /* Get pipe number */

  if (privep->epphy == 0)
    {
      pipe = 0;  /* DCP */
    }
  else
    {
      pipe = privep->epphy / 2;
      if (pipe >= RA_NLOGENDPOINTS)
        {
          return -EINVAL;
        }
    }

  flags = enter_critical_section();

  if (resume)
    {
      /* Clear stall */

      privep->stalled = false;

      if (pipe == 0)
        {
          /* DCP: Clear PIDSTALL, set PID=BUF */

          modifyreg16(R_USBFS_DCPCTR, (1 << 14), (1 << 9));
        }
      else
        {
          /* Data pipe: Clear PIDSTALL, set PID=BUF */

          modifyreg16(R_USBFS_PIPE1CTR + (pipe - 1) * 2,
                      (1 << 14), (1 << 9));
        }
    }
  else
    {
      /* Set stall */

      privep->stalled = true;

      if (pipe == 0)
        {
          /* DCP: Set PIDSTALL */

          modifyreg16(R_USBFS_DCPCTR, 0, (1 << 14));
        }
      else
        {
          /* Data pipe: Set PIDSTALL */

          modifyreg16(R_USBFS_PIPE1CTR + (pipe - 1) * 2, 0, (1 << 14));
        }
    }

  leave_critical_section(flags);

  return OK;
}

/****************************************************************************
 * Device Operations
 ****************************************************************************/

static struct usbdev_ep_s *ra_allocep(struct usbdev_s *dev,
                                     uint8_t epno, bool in, uint8_t eptype)
{
  struct ra_usbdev_s *priv = (struct ra_usbdev_s *)dev;
  struct ra_ep_s *privep;
  int i;

  /* Find an available endpoint */

  for (i = 1; i < RA_NPHYSENDPOINTS; i++)
    {
      privep = &priv->eplist[i];

      if (privep->eplog == 0)  /* Not in use */
        {
          privep->eplog = USB_EPNO(epno);
          if (in)
            {
              privep->eplog |= USB_DIR_IN;
            }

          privep->ep.ops = &g_epops;
          return &privep->ep;
        }
    }

  return NULL;
}

static void ra_freeep(struct usbdev_s *dev, struct usbdev_ep_s *ep)
{
  struct ra_ep_s *privep = (struct ra_ep_s *)ep;

  privep->eplog = 0;
}

static int ra_getframe(struct usbdev_s *dev)
{
  uint16_t frmnum = getreg16(R_USBFS_FRMNUM);
  return frmnum & 0x7ff;  /* 11-bit frame number */
}

static int ra_wakeup(struct usbdev_s *dev)
{
  /* TODO: Implement remote wakeup */

  return -ENOSYS;
}

static int ra_selfpowered(struct usbdev_s *dev, bool selfpowered)
{
  struct ra_usbdev_s *priv = (struct ra_usbdev_s *)dev;

  priv->selfpowered = selfpowered;
  return OK;
}

static int ra_pullup(struct usbdev_s *dev, bool enable)
{
  uinfo("USB pullup: %s\n", enable ? "ENABLE" : "DISABLE");

  if (enable)
    {
      /* Enable D+ pull-up to connect to host */

      modifyreg16(R_USBFS_SYSCFG, 0, R_USBFS_SYSCFG_DPRPU);
    }
  else
    {
      /* Disable D+ pull-up to disconnect from host */

      modifyreg16(R_USBFS_SYSCFG, R_USBFS_SYSCFG_DPRPU, 0);
    }

  return OK;
}

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: ra_usbdev_initialize
 *
 * Description:
 *   Initialize the USB device controller hardware and driver
 *
 ****************************************************************************/

void ra_usbdev_initialize(void)
{
  struct ra_usbdev_s *priv = &g_usbdev;
  int i;
  int ret;

  uinfo("Initializing RA8 USB device controller\n");

  /* Initialize the device structure */

  memset(priv, 0, sizeof(struct ra_usbdev_s));

  priv->usbdev.ops = &g_devops;
  priv->usbdev.ep0 = &priv->eplist[0].ep;
  priv->ep0state = EP0STATE_IDLE;

  /* Initialize endpoints */

  for (i = 0; i < RA_NPHYSENDPOINTS; i++)
    {
      struct ra_ep_s *privep = &priv->eplist[i];

      privep->ep.ops = &g_epops;
      privep->dev = priv;
      privep->epphy = i;
      privep->ep.maxpacket = (i == 0) ? RA_EP0_MAXPACKET : RA_BULK_MAXPACKET;
    }

  /* EP0 OUT and IN */

  priv->eplist[0].eplog = 0;
  priv->eplist[1].eplog = 0x80;

  /* Enable USB module stop control (MSTP) */

  ret = ra_mstp_start(RA_MSTP_USBFS);
  if (ret < 0)
    {
      uerr("ERROR: Failed to enable USB MSTP: %d\n", ret);
      return;
    }

  /* Initialize USB hardware */

  ret = ra_usbdev_hwinit(priv);
  if (ret < 0)
    {
      uerr("ERROR: Failed to initialize USB hardware: %d\n", ret);
      return;
    }

  /* Attach USB interrupt handler */

  priv->irq = ra_icu_attach(RA_ELC_USBFS_INT, ra_usbfs_interrupt,
                            priv, false);
  if (priv->irq < 0)
    {
      uerr("ERROR: Failed to attach USB interrupt: %d\n", priv->irq);
      return;
    }

  /* Set interrupt priority */

  ra_icu_set_priority(priv->irq, 12);

  /* Enable the interrupt */

  up_enable_irq(priv->irq);

  uinfo("USB device controller initialized successfully\n");
}

/****************************************************************************
 * Name: ra_usbdev_uninitialize
 *
 * Description:
 *   Uninitialize the USB device controller
 *
 ****************************************************************************/

void ra_usbdev_uninitialize(void)
{
  struct ra_usbdev_s *priv = &g_usbdev;

  /* Disable USB module */

  putreg16(0, R_USBFS_SYSCFG);

  /* Disable interrupt */

  if (priv->irq >= 0)
    {
      up_disable_irq(priv->irq);
      ra_icu_detach(priv->irq);
    }

  /* Stop USB module clock */

  ra_mstp_stop(RA_MSTP_USBFS);
}

/****************************************************************************
 * Name: ra_usbdev_connected
 *
 * Description:
 *   Check if USB device is connected and configured
 *
 ****************************************************************************/

bool ra_usbdev_connected(void)
{
  struct ra_usbdev_s *priv = &g_usbdev;

  return priv->attached && priv->configured;
}

#endif /* CONFIG_RA_USBDEV */
