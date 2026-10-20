#pragma once
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include "usb_device_state.h"
typedef struct { int dummy; } report_keyboard_t;
typedef struct { int dummy; } report_nkro_t;
typedef struct { void (*send_keyboard)(report_keyboard_t*); void (*send_nkro)(report_nkro_t*); } host_driver_t;
typedef struct { int state; int status; } USBDriver;
typedef struct { int dummy; } keyrecord_t;
#define USB_ACTIVE 1
#define USB_SUSPENDED 2
#define USB_DRIVER usbd
#define USBD1 usbd
extern USBDriver usbd;
host_driver_t *host_get_driver(void);
void host_set_driver(host_driver_t *d);
void host_keyboard_send(report_keyboard_t *r);
void host_nkro_send(report_nkro_t *r);
void restart_usb_driver(USBDriver *d);
void usbStop(USBDriver *d);
void usbDisconnectBus(USBDriver *d);
void usbWakeupHost(USBDriver *d);
void suspend_power_down(void);
void suspend_wakeup_init(void);
bool suspend_wakeup_condition(void);
uint32_t sync_timer_read32(void);
uint32_t sync_timer_elapsed32(uint32_t t);
void wait_ms(int);
#define dprintln(x)
