// Copyright 2024 Wind (@yelishang)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

#ifdef WIRELESS_ENABLE
#    include "wireless.h"
#endif

enum layers {
    WIN_B,
    WIN_FN,
    MAC_B,
    MAC_FN,
};

enum custom_keycodes {
    KC_BATQ = QK_USER_0, // show battery level on the number row while held
    KC_SBAR,             // toggle the side light bar / corner LEDs
};

typedef union {
    uint32_t raw;
    struct {
        uint8_t sidebar_off : 1;
    };
} userconf_t;
static userconf_t userconf;

static bool bat_show = false;

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [WIN_B] = LAYOUT_ansi(
		KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_F13,  KC_PSCR, KC_SCRL, KC_PAUS,
		KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_INS,  KC_HOME, KC_PGUP,
		KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, KC_DEL,  KC_END,  KC_PGDN,
		KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_NUHS, KC_ENT,
		KC_LSFT, KC_NUBS, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,          KC_RSFT,          KC_UP,
		KC_LCTL, KC_LGUI, KC_LALT, KC_LNG2,                   KC_SPC,                    KC_LNG1, KC_RALT,MO(WIN_FN),KC_APP,KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT
    ),

    [WIN_FN] = LAYOUT_ansi(
		EE_CLR,  KC_MYCM, KC_WHOM, KC_MAIL, KC_CALC, KC_MSEL, KC_MSTP, KC_MPRV, KC_MPLY, KC_MNXT, KC_MUTE, KC_VOLD, KC_VOLU, _______, _______, _______, _______,
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, RGB_TOG, RGB_MOD, _______, _______,
		DF(2),   KC_BT1,  KC_BT2,  KC_BT3,  KC_2G4,  KC_USB,  _______, RGB_SAD, RGB_SAI, _______, _______, _______, _______, _______, RGB_HUI, KC_SBAR, _______,
		_______, _______, _______, _______, _______, _______, KC_SCRL, KC_PAUS, KC_HOME, KC_END,  _______, _______, _______, _______,
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,          RGB_VAI,
		_______, GU_TOGG, _______, _______,                   KC_BATQ,                   _______, _______, _______, _______, _______, RGB_SPD, RGB_VAD, RGB_SPI
    ),

    [MAC_B] = LAYOUT_ansi(
		KC_ESC,  KC_BRID, KC_BRIU, KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_MPRV, KC_MPLY, KC_MNXT, KC_MUTE, KC_VOLD, KC_VOLU, KC_F13,  KC_PSCR, KC_SCRL, KC_PAUS,
		KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_INS,  KC_HOME, KC_PGUP,
		KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, KC_DEL,  KC_END,  KC_PGDN,
		KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_NUHS, KC_ENT,
		KC_LSFT, KC_NUBS, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,          KC_RSFT,          KC_UP,
		KC_LCTL, KC_LALT, KC_LGUI, KC_LNG2,                   KC_SPC,                    KC_LNG1, KC_RGUI,MO(MAC_FN),KC_APP,KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT
    ),

    [MAC_FN] = LAYOUT_ansi(
		EE_CLR,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______, _______, _______, _______,
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, RGB_TOG, RGB_MOD, _______, _______,
		DF(0),   KC_BT1,  KC_BT2,  KC_BT3,  KC_2G4,  KC_USB,  _______, RGB_SAD, RGB_SAI, _______, _______, _______, _______, _______, RGB_HUI, KC_SBAR, _______,
		_______, _______, _______, _______, _______, _______, KC_SCRL, KC_PAUS, KC_HOME, KC_END,  _______, _______, _______, _______,
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,          RGB_VAI,
		_______, _______, _______, _______,                   KC_BATQ,                   _______, _______, _______, _______, _______, RGB_SPD, RGB_VAD, RGB_SPI
    )
};
// clang-format on

void eeconfig_init_user(void) {
    userconf.raw = 0;
    eeconfig_update_user(userconf.raw);
}

void keyboard_post_init_user(void) {
    userconf.raw = eeconfig_read_user();
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KC_BATQ:
            bat_show = record->event.pressed;
#ifdef WIRELESS_ENABLE
            if (record->event.pressed) {
                md_inquire_bat(); // refresh the cached battery level
            }
#endif
            return false;
        case KC_SBAR:
            if (record->event.pressed) {
                userconf.sidebar_off ^= 1;
                eeconfig_update_user(userconf.raw);
            }
            return false;
        default:
            return true;
    }
}

// Number-row LED indices: the row-1 LEDs are chained right-to-left, so key
// "1" ([1,1]) is LED 32 down to key "0" ([1,10]) at LED 23.
static uint8_t digit_led_index(uint8_t digit) {
    return 33 - digit;
}

bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    if (userconf.sidebar_off) {
        for (uint8_t i = 0; i < RGB_MATRIX_LED_COUNT; i++) {
            if (g_led_config.flags[i] & LED_FLAG_UNDERGLOW) {
                rgb_matrix_set_color(i, 0x00, 0x00, 0x00);
            }
        }
    }

    if (bat_show) {
        uint8_t bat = 100;
#ifdef WIRELESS_ENABLE
        bat = *md_getp_bat();
#endif
        uint8_t lit = (bat + 9) / 10; // 1 key per 10%
        for (uint8_t d = 1; d <= 10; d++) {
            uint8_t idx = digit_led_index(d);
            if (d <= lit) {
                if (bat <= 20) {
                    rgb_matrix_set_color(idx, 0xFF, 0x00, 0x00);
                } else if (bat <= 50) {
                    rgb_matrix_set_color(idx, 0xFF, 0xA5, 0x00);
                } else {
                    rgb_matrix_set_color(idx, 0x00, 0xFF, 0x00);
                }
            } else {
                rgb_matrix_set_color(idx, 0x00, 0x00, 0x00);
            }
        }
    }

    return true;
}
