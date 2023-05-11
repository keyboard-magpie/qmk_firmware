#include QMK_KEYBOARD_H
#include "features/achordion.h"

enum layers {
    _DEF,
    _EXT,
    _SYM,
    _FUN,
    _NUM,
};

#define EXT MO(_EXT)
#define SYM MO(_SYM)
#define NUM MO(_NUM)

#define BACK LSG(KC_LBRC)
#define FWD  LSG(KC_RBRC)

// Home row mods
#define HOME_A LALT_T(KC_A)
#define HOME_R LGUI_T(KC_R)
#define HOME_S LSFT_T(KC_S)
#define HOME_T LCTL_T(KC_T)

#define HOME_N RCTL_T(KC_N)
#define HOME_E RSFT_T(KC_E)
#define HOME_I LGUI_T(KC_I)
#define HOME_O LALT_T(KC_O)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[_DEF] = LAYOUT(
        KC_Q,       KC_W,       KC_F,       KC_P,       KC_B,       KC_J,       KC_L,       KC_U,       KC_Y,       KC_QUOT,
        HOME_A,     HOME_R,     HOME_S,     HOME_T,     KC_G,       KC_M,       HOME_N,     HOME_E,     HOME_I,     HOME_O,
        KC_Z,       KC_X,       KC_C,       KC_D,       KC_V,       KC_K,       KC_H,       KC_COMM,    KC_DOT,     KC_SLSH,
                                            EXT,        KC_LSFT,    KC_SPC,     SYM
    ),

	[_EXT] = LAYOUT(
        QK_GESC,    BACK,       KC_NO,      FWD,        KC_NO,      KC_PGUP,    KC_HOME,    KC_UP,      KC_END,     CW_TOGG,
        KC_LALT,    KC_LGUI,    KC_LSFT,    KC_LCTL,    KC_NO,      KC_PGDN,    KC_LEFT,    KC_DOWN,    KC_RGHT,    KC_DEL,
        G(KC_Z),    G(KC_X),    G(KC_C),    KC_TAB,     G(KC_V),    A(KC_BSPC), KC_BSPC,    KC_NO,      KC_NO,      KC_NO,
                                            _______,    _______,    KC_ENT,     _______
    ),

	[_SYM] = LAYOUT(
        KC_EXLM,    KC_AT,      KC_HASH,    KC_DLR,     KC_PERC,    KC_EQL,     KC_GRV,     KC_COLN,    KC_SCLN,    KC_PLUS,
        KC_LALT,    KC_LGUI,    KC_LSFT,    KC_LCTL,    KC_CIRC,    KC_ASTR,    KC_LPRN,    KC_LCBR,    KC_LBRC,    KC_MINS,
        KC_NO,      KC_NO,      KC_BSLS,    KC_PIPE,    KC_AMPR,    KC_TILD,    KC_RPRN,    KC_RCBR,    KC_RBRC,    KC_UNDS,
                                            _______,    NUM,        _______,    _______
    ),

    [_NUM] = LAYOUT(
        KC_NO,      KC_NO,      KC_NO,       KC_NO,     KC_NO,      KC_EQL,     KC_7,       KC_8,       KC_9,       KC_PPLS,
        KC_LALT,    KC_LGUI,    KC_LSFT,     KC_LCTL,   KC_NO,      KC_ASTR,    KC_4,       KC_5,       KC_6,       KC_PMNS,
        KC_NO,      KC_NO,      KC_NO,       KC_BSPC,   KC_NO,      KC_0,       KC_1,       KC_2,       KC_3,       KC_SLSH,
                                            _______,    _______,    _______,    _______
    ),

	[_FUN] = LAYOUT(
        KC_MSTP,    KC_MPRV,    KC_MPLY,    KC_MNXT,    KC_BRIU,    KC_F12,     KC_F7,      KC_F8,      KC_F9,      G(KC_EQL),
        KC_LALT,    KC_LGUI,    KC_LSFT,    KC_LCTL,    KC_BRID,    KC_F11,     KC_F4,      KC_F5,      KC_F6,      G(KC_MINS),
        KC_NO,      KC_VOLD,    KC_MUTE,    KC_VOLU,    KC_NO,      KC_F10,     KC_F1,      KC_F2,      KC_F3,      G(KC_0),
                                            _______,    _______,    _______,    _______
    ),
};

void matrix_scan_user(void) {
  achordion_task();
}

bool achordion_eager_mod(uint8_t mod) {
  switch (mod) {
    case MOD_LSFT:
    case MOD_RSFT:
    case MOD_LGUI:
    case MOD_RGUI:
      return true;  // Eagerly apply Shift and Gui mods.

    default:
      return false;
  }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!process_achordion(keycode, record)) { return false; }

    return true;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    return update_tri_layer_state(state, _EXT, _SYM, _FUN);
}

void keyboard_pre_init_user(void) {
  // Set our LED pin as output
  setPinOutput(24);
  // Turn the LED off
  // (Due to technical reasons, high is off and low is on)
  writePinHigh(24);
}

#ifdef RGB_MATRIX_ENABLE
void keyboard_post_init_user(void) {
  rgb_matrix_enable_noeeprom();
  rgb_matrix_sethsv_noeeprom(HSV_AZURE);
  rgb_matrix_mode_noeeprom(RGB_MATRIX_SOLID_COLOR);
}

bool rgb_matrix_indicators_user(void) {
    if (get_oneshot_mods() & MOD_MASK_ALT) {
        rgb_matrix_set_color(11, RGB_RED);
    }
    if (get_oneshot_mods() & MOD_MASK_GUI) {
        rgb_matrix_set_color(12, RGB_RED);
    }
    if (get_oneshot_mods() & MOD_MASK_SHIFT) {
        rgb_matrix_set_color(13, RGB_RED);
    }
    if (get_oneshot_mods() & MOD_MASK_CTRL) {
        rgb_matrix_set_color(14, RGB_RED);
    }

    return true;
}
#endif
