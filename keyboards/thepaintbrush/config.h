// Copyright (c) 2021 Mike "KemoNine" Crosson
// SPDX-License-Identifier: Apache-2.0
#pragma once

/* USB Device descriptor parameter */

/* Board layout */
#define MATRIX_ROWS 2
#define MATRIX_COLS 4

#define DIRECT_PINS {{ F4, F5, F6, F7 }, { B1, B3, B2, B6 }}

/* Prevent jitters in key presses */
