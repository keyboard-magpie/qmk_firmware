// Copyright 2024 George Norton (@george-norton)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {[0] = LAYOUT(KC_BTN1, KC_BTN2, LT(1, KC_BTN3), KC_BTN4, KC_BTN5),
                                                              [1] = LAYOUT(QK_BOOT, RGB_MOD, KC_TRNS, RGB_RMOD, EE_CLR),};

