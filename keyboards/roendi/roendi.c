// Copyright 2022 bom
// SPDX-License-Identifier: GPL-2.0-or-later

#include "quantum.h"
#include "roendi.h"
#include "test.qgf.h"

painter_device_t       roendi_display;
painter_image_handle_t avatar_image;

void keyboard_post_init_kb(void) {
    roendi_display = qp_gc9a01_make_spi_device(240, 240, DISPLAY_CS, DISPLAY_DC, DISPLAY_RST, 1, 0);
    qp_init(roendi_display, QP_ROTATION_0);
    avatar_image = qp_load_image_mem(gfx_test);
    qp_drawimage(roendi_display, 0, 0, avatar_image);
    qp_flush(roendi_display);
    keyboard_post_init_user();

#ifdef ENCODER_ENABLE
bool encoder_update_kb(uint8_t index, bool clockwise) {
    if (!encoder_update_user(index, clockwise)) { return false; }
    if (clockwise) {
        tap_code(KC_VOLU);
    } else {
        tap_code(KC_VOLD);
    }
    return true;
}
#endif

void spi_init(void) {
    static bool is_initialised = false;
    if (!is_initialised) {
        is_initialised = true;

        // Try releasing special pins for a short time
        setPinInput(SPI_SCK_PIN);
        setPinInput(SPI_MOSI_PIN);

        chThdSleepMilliseconds(10);
#if defined(USE_GPIOV1)
        palSetPadMode(PAL_PORT(SPI_SCK_PIN), PAL_PAD(SPI_SCK_PIN), SPI_SCK_PAL_MODE);
        palSetPadMode(PAL_PORT(SPI_MOSI_PIN), PAL_PAD(SPI_MOSI_PIN), SPI_MOSI_PAL_MODE);
#else
        palSetPadMode(PAL_PORT(SPI_SCK_PIN), PAL_PAD(SPI_SCK_PIN), SPI_SCK_FLAGS);
        palSetPadMode(PAL_PORT(SPI_MOSI_PIN), PAL_PAD(SPI_MOSI_PIN), SPI_MOSI_FLAGS);
#endif
        spiStop(&SPI_DRIVER);
        currentSlavePin = NO_PIN;
    }
}