// Copyright 2024 TODO (@TODO)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

/*
 * Feature disable options
 *  These options are also useful to firmware size reduction.
 */

/* disable debug print */
//#define NO_DEBUG

/* disable print */
//#define NO_PRINT

/* disable action features */
#define NO_ACTION_LAYER
//#define NO_ACTION_TAPPING
//#define NO_ACTION_ONESHOT
// #define ENCODERS_PAD_A { GP29, GP2 }
// #define ENCODERS_PAD_B { GP1, GP4 }
#define ENCODERS_PAD_A { GP29 }
#define ENCODERS_PAD_B { GP1 }
#define ENCODER_RESOLUTION 2
// #define ENCODER_MAP_KEY_DELAY 10
#define DYNAMIC_KEYMAP_LAYER_COUNT 1