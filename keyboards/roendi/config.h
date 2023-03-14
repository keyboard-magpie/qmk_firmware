// Copyright 2023 Tom Barnes (@Tom Barnes)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#define SPI_DRIVER SPID1
#define SPI_SCK_PIN B13
#define SPI_SCK_PAL_MODE 5
#define SPI_MOSI_PIN B15
#define SPI_MOSI_PAL_MODE 5
#define SPI_MISO_PIN B14
#define SPI_MISO_PAL_MODE 5

#define DISPLAY_RST B14
#define DISPLAY_CS B12
#define DISPLAY_DC A8

#define QUANTUM_PAINTER_SUPPORTS_256_PALETTE true
/*
 * Feature disable options
 *  These options are also useful to firmware size reduction.
 */

/* disable debug print */
//#define NO_DEBUG

/* disable print */
//#define NO_PRINT

/* disable action features */
//#define NO_ACTION_LAYER
//#define NO_ACTION_TAPPING
//#define NO_ACTION_ONESHOT
