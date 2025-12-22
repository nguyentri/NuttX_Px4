/****************************************************************************
 * arch/arm/src/ra8/ra8_usbdev.h
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

#ifndef __ARCH_ARM_SRC_RA8_RA8_USBDEV_H
#define __ARCH_ARM_SRC_RA8_RA8_USBDEV_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>
#include <nuttx/usb/usbdev.h>

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* Configuration */

#ifndef CONFIG_USBDEV_EP0_MAXSIZE
#  define CONFIG_USBDEV_EP0_MAXSIZE 64
#endif

#ifndef CONFIG_USBDEV_MAXPOWER
#  define CONFIG_USBDEV_MAXPOWER 100  /* mA */
#endif

/* Number of endpoints */

#define RA_NLOGENDPOINTS     10     /* DCP (EP0) + 9 pipes */
#define RA_NPHYSENDPOINTS    20     /* x2 for IN and OUT directions */

/* Endpoint numbers */

#define RA_EP0_OUT           0
#define RA_EP0_IN            1

/* Pipe assignments for CDC-ACM */

#define RA_BULK_IN_PIPE      1      /* CDC bulk IN (TX to host) */
#define RA_BULK_OUT_PIPE     2      /* CDC bulk OUT (RX from host) */
#define RA_INT_IN_PIPE       3      /* CDC interrupt IN (notifications) */

/* Maximum packet sizes */

#define RA_EP0_MAXPACKET     64     /* Control endpoint */
#define RA_BULK_MAXPACKET    64     /* Full-speed bulk */
#define RA_INT_MAXPACKET     16     /* Interrupt endpoint */

/* EP0 state machine states */

#define EP0STATE_IDLE        0
#define EP0STATE_SETUP_OUT   1      /* SET/CLEAR request */
#define EP0STATE_SETUP_IN    2      /* GET request */
#define EP0STATE_DATA_IN     3
#define EP0STATE_DATA_OUT    4
#define EP0STATE_STATUS_IN   5
#define EP0STATE_STATUS_OUT  6
#define EP0STATE_STALLED     7

/* Trace error codes */

#define RA_TRACEERR_ALLOCFAIL           0x0001
#define RA_TRACEERR_BADCLEARFEATURE     0x0002
#define RA_TRACEERR_BADDEVGETSTATUS     0x0003
#define RA_TRACEERR_BADEPNO             0x0004
#define RA_TRACEERR_BADEPGETSTATUS      0x0005
#define RA_TRACEERR_BADEPTYPE           0x0006
#define RA_TRACEERR_BADGETCONFIG        0x0007
#define RA_TRACEERR_BADGETSETDESC       0x0008
#define RA_TRACEERR_BADGETSTATUS        0x0009
#define RA_TRACEERR_BADSETADDRESS       0x000a
#define RA_TRACEERR_BADSETCONFIG        0x000b
#define RA_TRACEERR_BADSETFEATURE       0x000c
#define RA_TRACEERR_BINDFAILED          0x000d
#define RA_TRACEERR_DISPATCHSTALL       0x000e
#define RA_TRACEERR_DRIVER              0x000f
#define RA_TRACEERR_DRIVERREGISTERED    0x0010
#define RA_TRACEERR_EP0SETUPSTALLED     0x0011
#define RA_TRACEERR_EPINNULLPACKET      0x0012
#define RA_TRACEERR_EPOUTNULLPACKET     0x0013
#define RA_TRACEERR_INVALIDCTRLREQ      0x0014
#define RA_TRACEERR_INVALIDPARMS        0x0015
#define RA_TRACEERR_IRQREGISTRATION     0x0016
#define RA_TRACEERR_NOEP                0x0017
#define RA_TRACEERR_NOTCONFIGURED       0x0018
#define RA_TRACEERR_REQABORTED          0x0019

/* Trace interrupt codes */

#define RA_TRACEINTID_USB               0x0001
#define RA_TRACEINTID_CLEARFEATURE      0x0002
#define RA_TRACEINTID_DEVGETSTATUS      0x0003
#define RA_TRACEINTID_DEVRESET          0x0004
#define RA_TRACEINTID_DISPATCH          0x0005
#define RA_TRACEINTID_EP0COMPLETE       0x0006
#define RA_TRACEINTID_EP0SETUP          0x0007
#define RA_TRACEINTID_EPGETSTATUS       0x0008
#define RA_TRACEINTID_EPIN              0x0009
#define RA_TRACEINTID_EPINQEMPTY        0x000a
#define RA_TRACEINTID_EP0INSETADDRESS   0x000b
#define RA_TRACEINTID_EPOUT             0x000c
#define RA_TRACEINTID_EPOUTQEMPTY       0x000d
#define RA_TRACEINTID_EP0SETUPSETADDRESS 0x000e
#define RA_TRACEINTID_GETCONFIG         0x000f
#define RA_TRACEINTID_GETSETDESC        0x0010
#define RA_TRACEINTID_GETSETIF          0x0011
#define RA_TRACEINTID_GETSTATUS         0x0012
#define RA_TRACEINTID_SETCONFIG         0x0013
#define RA_TRACEINTID_SETFEATURE        0x0014
#define RA_TRACEINTID_SUSPENDED         0x0015
#define RA_TRACEINTID_RESUMED           0x0016

/****************************************************************************
 * Public Types
 ****************************************************************************/

/* Request container for singly-linked queue */

struct ra_req_s
{
  struct usbdev_req_s req;       /* Standard USB request */
  struct ra_req_s    *flink;     /* Next request in queue */
};

/* Endpoint state */

struct ra_ep_s
{
  struct usbdev_ep_s  ep;        /* Standard endpoint structure */
  struct ra_usbdev_s *dev;       /* Back reference to device */
  struct ra_req_s    *head;      /* Request queue head */
  struct ra_req_s    *tail;      /* Request queue tail */
  uint8_t             epphy;     /* Physical endpoint (pipe) number */
  uint8_t             eplog;     /* Logical endpoint address */
  uint8_t             stalled:1; /* Endpoint stalled */
  uint8_t             active:1;  /* Transfer in progress */
  uint16_t            txlen;     /* Bytes remaining to transmit */
  uint16_t            rxlen;     /* Bytes remaining to receive */
};

/* USB device controller state */

struct ra_usbdev_s
{
  struct usbdev_s              usbdev;    /* Standard USB device */
  struct usbdevclass_driver_s *driver;    /* Bound class driver */

  /* Device state */

  uint8_t  ep0state;                      /* EP0 state machine */
  uint8_t  paddr;                         /* USB device address */
  uint8_t  selfpowered:1;                 /* Self-powered flag */
  uint8_t  paddrset:1;                    /* Address has been set */
  uint8_t  attached:1;                    /* Host attached */
  uint8_t  suspended:1;                   /* Suspended state */
  uint8_t  configured:1;                  /* Configured state */

  /* EP0 control transfer buffer */

  uint8_t  ep0buf[64];
  uint16_t ep0buf_len;
  struct usb_ctrlreq_s ep0ctrl;

  /* Endpoint array */

  struct ra_ep_s eplist[RA_NPHYSENDPOINTS];

  /* IRQ number for cleanup */

  int      irq;
};

/****************************************************************************
 * Private Function Prototypes
 ****************************************************************************/

/* Request queue operations */

static struct ra_req_s *ra_rqdequeue(struct ra_ep_s *privep);
static bool ra_rqenqueue(struct ra_ep_s *privep, struct ra_req_s *req);

/* Low level FIFO operations */

static void ra_fifo_write(uint8_t pipe, const uint8_t *data, size_t len);
static size_t ra_fifo_read(uint8_t pipe, uint8_t *data, size_t maxlen);

/* Endpoint operations */

static int ra_epconfigure(struct usbdev_ep_s *ep,
                          const struct usb_epdesc_s *desc, bool last);
static int ra_epdisable(struct usbdev_ep_s *ep);
static struct usbdev_req_s *ra_epallocreq(struct usbdev_ep_s *ep);
static void ra_epfreereq(struct usbdev_ep_s *ep, struct usbdev_req_s *req);
static int ra_epsubmit(struct usbdev_ep_s *ep, struct usbdev_req_s *req);
static int ra_epcancel(struct usbdev_ep_s *ep, struct usbdev_req_s *req);
static int ra_epstall(struct usbdev_ep_s *ep, bool resume);

/* Device operations */

static struct usbdev_ep_s *ra_allocep(struct usbdev_s *dev,
                                      uint8_t epno, bool in, uint8_t eptype);
static void ra_freeep(struct usbdev_s *dev, struct usbdev_ep_s *ep);
static int ra_getframe(struct usbdev_s *dev);
static int ra_wakeup(struct usbdev_s *dev);
static int ra_selfpowered(struct usbdev_s *dev, bool selfpowered);
static int ra_pullup(struct usbdev_s *dev, bool enable);

/* Interrupt handling */

static int ra_usbfs_interrupt(int irq, void *context, void *arg);

#endif /* __ARCH_ARM_SRC_RA8_RA8_USBDEV_H */
