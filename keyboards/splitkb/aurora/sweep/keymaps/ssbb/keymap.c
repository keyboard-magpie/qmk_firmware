#include QMK_KEYBOARD_H
#include "features/achordion.h"

enum layers {
    _DEF,
    _EXT,
    _SYM,
    _FUN,
};

#define EXT MO(_EXT)
#define SYM MO(_SYM)

enum my_keycodes {
    OSM_LGUI = SAFE_RANGE,
    OSM_LALT,
    OSM_LSFT,
    OSM_LCTL,
};

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

// #define HOME_A KC_A
// #define HOME_R KC_R
// #define HOME_S KC_S
// #define HOME_T KC_T

// #define HOME_N KC_N
// #define HOME_E KC_E
// #define HOME_I KC_I
// #define HOME_O KC_O

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[_DEF] = LAYOUT(
        KC_Q,       KC_W,       KC_F,       KC_P,       KC_B,       KC_J,       KC_L,       KC_U,       KC_Y,       KC_QUOT,
        HOME_A,     HOME_R,     HOME_S,     HOME_T,     KC_G,       KC_M,       HOME_N,     HOME_E,     HOME_I,     HOME_O,
        KC_Z,       KC_X,       KC_C,       KC_D,       KC_V,       KC_K,       KC_H,       KC_COMM,    KC_DOT,     KC_SLSH,
                                            EXT,        KC_LSFT,    KC_SPC,     SYM
    ),

	[_EXT] = LAYOUT(
        QK_GESC,    BACK,       G(KC_F),    FWD,        G(KC_B),    KC_PGUP,    KC_HOME,    KC_UP,      KC_END,     CW_TOGG,
        OSM_LALT,   OSM_LGUI,   OSM_LSFT,   OSM_LCTL,   C(KC_G),    KC_PGDN,    KC_LEFT,    KC_DOWN,    KC_RGHT,    KC_DEL,
        G(KC_Z),    G(KC_X),    G(KC_C),    KC_TAB,     G(KC_V),    A(KC_BSPC), KC_BSPC,    KC_NO,      KC_NO,      KC_NO,
                                            _______,    _______,    KC_ENT,     _______
    ),

	[_SYM] = LAYOUT(
        KC_7,       KC_5,       KC_3,       KC_1,       KC_9,       KC_8,       KC_0,       KC_2,       KC_4,       KC_6,
        KC_LT,      KC_PERC,    KC_LCBR,    KC_LPRN,    KC_LBRC,    KC_EQL,     KC_UNDS,    KC_COLN,    KC_GRV,     KC_PIPE,
        KC_GT,      KC_DLR,     KC_RCBR,    KC_RPRN,    KC_RBRC,    KC_PLUS,    KC_MINS,    KC_SCLN,    KC_TILD,    KC_BSLS,
                                            _______,    _______,    _______,    _______
    ),

	[_FUN] = LAYOUT(
        QK_BOOT,    KC_MPRV,    KC_MPLY,    KC_MNXT,    C(KC_BRIU), G(KC_EQL),  KC_F7,      KC_F8,      KC_F9,      KC_F10,
        EE_CLR,     KC_VOLD,    KC_MUTE,    KC_VOLU,    C(KC_BRID), G(KC_MINS), KC_F4,      KC_F5,      KC_F6,      KC_F11,
        QK_RBT,     DT_DOWN,    DT_PRNT,    DT_UP,      KC_NO,      G(KC_0),    KC_F1,      KC_F2,      KC_F3,      KC_F12,
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

    switch (keycode) {
        case OSM_LGUI:
            if (record->event.pressed) {
                register_mods(MOD_BIT(KC_LGUI));
                add_oneshot_mods(MOD_BIT(KC_LGUI));
            } else {
                unregister_mods(MOD_BIT(KC_LGUI));
            }
            return false;

        case OSM_LALT:
            if (record->event.pressed) {
                register_mods(MOD_BIT(KC_LALT));
                add_oneshot_mods(MOD_BIT(KC_LALT));
            } else {
                unregister_mods(MOD_BIT(KC_LALT));
            }
            return false;

        case OSM_LCTL:
            if (record->event.pressed) {
                register_mods(MOD_BIT(KC_LCTL));
                add_oneshot_mods(MOD_BIT(KC_LCTL));
            } else {
                unregister_mods(MOD_BIT(KC_LCTL));
            }
            return false;

        case OSM_LSFT:
            if (record->event.pressed) {
                register_mods(MOD_BIT(KC_LSFT));
                add_oneshot_mods(MOD_BIT(KC_LSFT));
            } else {
                unregister_mods(MOD_BIT(KC_LSFT));
            }
            return false;

        default:
            break;
    }

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
