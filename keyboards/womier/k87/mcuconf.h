// Copyright 2024 Wind (@yelishang)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include_next <mcuconf.h>

#undef WB32_USB_HOST_WAKEUP_DURATION
#define WB32_USB_HOST_WAKEUP_DURATION 2

#undef WB32_SERIAL_USE_UART1
#define WB32_SERIAL_USE_UART1 TRUE

#undef WB32_SERIAL_USE_UART3
#define WB32_SERIAL_USE_UART3 TRUE

#undef WB32_SPI_USE_QSPI
#define WB32_SPI_USE_QSPI TRUE

#undef WB32_I2C_USE_I2C1
#define WB32_I2C_USE_I2C1 TRUE

/* system clock set to 96Mhz */
#undef WB32_PLLDIV_VALUE
#define WB32_PLLDIV_VALUE 2

#undef WB32_PLLMUL_VALUE
#define WB32_PLLMUL_VALUE 16

#undef WB32_USBPRE
#define WB32_USBPRE WB32_USBPRE_DIV2
