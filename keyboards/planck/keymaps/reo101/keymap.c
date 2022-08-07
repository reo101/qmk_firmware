/* Copyright 2015-2021 Jack Humbert
 * Copyright 2022-2022 Pavel Atanasov
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include QMK_KEYBOARD_H
#include "muse.h"
#include "eeprom.h"

enum planck_layers {
    _QWERTY,
    _COLEMAK_DH,
    _LOWER,
    _RAISE,
    // _OG_LOWER,
    // _OG_RAISE,
    _ADJUST,
};

enum planck_keycodes {
    QWERTY = SAFE_RANGE,
    COLEMAK_DH,
    BACKLIT,
};

// #define OG_LOWER MO(_OG_LOWER)
// #define OG_RAISE MO(_OG_RAISE)

#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)

#define BTR_ESC MT(MOD_LCTL, KC_ESCAPE)
#define BTR_ENT MT(MOD_RSFT, KC_ENTER)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 * ,-----------------------------------------------------------------------------------.
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Esc  |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |  '   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Brite| Ctrl | GUI  | Alt  |Lower |    Space    |Raise | Left | Down |  Up  |Right |
 * `-----------------------------------------------------------------------------------'
 */
[_QWERTY] = LAYOUT_planck_grid(
    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
    BTR_ESC, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, BTR_ENT,
    BACKLIT, KC_LCTL, KC_LGUI, KC_LALT, LOWER,   KC_SPC,  KC_SPC,  RAISE,   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT
),

/* Colemak DH
 * ,-----------------------------------------------------------------------------------.
 * | Tab  |   Q  |   W  |   F  |   P  |   G  |   J  |   L  |   U  |   Y  |   ;  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Esc  |   A  |   R  |   S  |   T  |   V  |   M  |   N  |   E  |   I  |   O  |  '   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   D  |   B  |   K  |   H  |   ,  |   .  |   /  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Brite| Ctrl | GUI  | Alt  |Lower |    Space    |Raise | Left | Down |  Up  |Right |
 * `-----------------------------------------------------------------------------------'
 */
[_COLEMAK_DH] = LAYOUT_planck_grid(
    KC_TAB,  KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,    KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN, KC_BSPC,
    KC_ESC,  KC_A,    KC_R,    KC_S,    KC_T,    KC_V,    KC_M,    KC_N,    KC_E,    KC_I,    KC_O,    KC_QUOT,
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_D,    KC_B,    KC_K,    KC_H,    KC_COMM, KC_DOT,  KC_SLSH, KC_ENT ,
    BACKLIT, KC_LCTL, KC_LGUI, KC_LALT, LOWER,   KC_SPC,  KC_SPC,  RAISE,   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT
),

/* Lower
 * ,-----------------------------------------------------------------------------------.
 * |   ~  |   !  |   @  |   #  |   $  |   %  |   ^  |   &  |   *  |   (  |   )  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Del  |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |   _  |   +  |   {  |   }  |  |   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |ISO ~ |ISO | | Home | End  |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      | Next | Vol- | Vol+ | Play |
 * `-----------------------------------------------------------------------------------'
 */
[_LOWER] = LAYOUT_planck_grid(
    KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR,    KC_ASTR,    KC_LPRN, KC_RPRN, KC_BSPC,
    KC_DEL,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_UNDS,    KC_PLUS,    KC_LCBR, KC_RCBR, KC_PIPE,
    _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  S(KC_NUHS), S(KC_NUBS), KC_HOME, KC_END,  _______,
    _______, _______, _______, _______, _______, _______, _______, _______,    KC_MNXT,    KC_VOLD, KC_VOLU, KC_MPLY
),

/* Raise
 * ,-----------------------------------------------------------------------------------.
 * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Del  |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |   -  |   =  |   [  |   ]  |  \   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |ISO # |ISO / |Pg Up |Pg Dn |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      | Next | Vol- | Vol+ | Play |
 * `-----------------------------------------------------------------------------------'
 */
[_RAISE] = LAYOUT_planck_grid(
    KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
    KC_DEL,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS,
    _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_NUHS, KC_NUBS, KC_PGUP, KC_PGDN, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY
),

// /* OG Lower
//  * ,-----------------------------------------------------------------------------------.
//  * |   ~  |   !  |   @  |   #  |   $  |   %  |   ^  |   &  |   *  |   (  |   )  | Bksp |
//  * |------+------+------+------+------+------+------+------+------+------+------+------|
//  * | Del  |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |   _  |   +  |   {  |   }  |  |   |
//  * |------+------+------+------+------+------+------+------+------+------+------+------|
//  * |      |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |ISO ~ |ISO | | Home | End  |      |
//  * |------+------+------+------+------+------+------+------+------+------+------+------|
//  * |      |      |      |      |      |             |      | Next | Vol- | Vol+ | Play |
//  * `-----------------------------------------------------------------------------------'
//  */
// [_OG_LOWER] = LAYOUT_planck_grid(
//     KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR,    KC_ASTR,    KC_LPRN, KC_RPRN, KC_BSPC,
//     KC_DEL,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_UNDS,    KC_PLUS,    KC_LCBR, KC_RCBR, KC_PIPE,
//     _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  S(KC_NUHS), S(KC_NUBS), KC_HOME, KC_END,  _______,
//     _______, _______, _______, _______, _______, _______, _______, _______,    KC_MNXT,    KC_VOLD, KC_VOLU, KC_MPLY
// ),

// /* OG Raise
//  * ,-----------------------------------------------------------------------------------.
//  * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Bksp |
//  * |------+------+------+------+------+------+------+------+------+------+------+------|
//  * | Del  |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |   -  |   =  |   [  |   ]  |  \   |
//  * |------+------+------+------+------+------+------+------+------+------+------+------|
//  * |      |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |ISO # |ISO / |Pg Up |Pg Dn |      |
//  * |------+------+------+------+------+------+------+------+------+------+------+------|
//  * |      |      |      |      |      |             |      | Next | Vol- | Vol+ | Play |
//  * `-----------------------------------------------------------------------------------'
//  */
// [_OG_RAISE] = LAYOUT_planck_grid(
//     KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
//     KC_DEL,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS,
//     _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_NUHS, KC_NUBS, KC_PGUP, KC_PGDN, _______,
//     _______, _______, _______, _______, _______, _______, _______, _______, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY
// ),

/* Adjust (Lower + Raise)
 *                      v------------------------RGB CONTROL--------------------v
 * ,-----------------------------------------------------------------------------------.
 * |      |Reset |Debug | RGB  |RGBMOD| HUE+ | HUE- | SAT+ | SAT- |BRGTH+|BRGTH-|  Del |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |MUSmod|Aud on|Audoff|AGnorm|AGswap|Qwerty|Colemk|      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |Voice-|Voice+|Mus on|Musoff|MIDIon|MIDIof|TermOn|TermOf|      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_ADJUST] = LAYOUT_planck_grid(
    _______, QK_BOOT, DEBUG,   RGB_TOG, RGB_MOD, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD,    RGB_VAI, RGB_VAD, KC_DEL ,
    _______, _______, MU_MOD,  AU_ON,   AU_OFF,  AG_NORM, AG_SWAP, QWERTY,  COLEMAK_DH, _______, _______, _______,
    _______, MUV_DE,  MUV_IN,  MU_ON,   MU_OFF,  MI_ON,   MI_OFF,  TERM_ON, TERM_OFF,   _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______,    _______, _______, _______
)

};

// RGB Lighting

rgb_config_t rgb_matrix_config;

const uint8_t PROGMEM ledmaps[][DRIVER_LED_TOTAL][3] = {
    [_QWERTY] = {
        {  0,   0,   0}, {  0,   0,   0}, {  0,   0,   0}, {  0,   0,   0}, {  0,   0,   0}, {  0,   0,   0 }, {  0,  0,  0 }, {  0,   0,   0}, {  0,   0,   0}, {  0,   0,   0}, {  0,   0,   0}, {  0,   0,   0},
        {  0,   0,   0}, {  0,   0,   0}, {  0,   0,   0}, {  0,   0,   0}, {  0,   0,   0}, {  0,   0,   0 }, {  0,  0,  0 }, {  0,   0,   0}, {  0,   0,   0}, {  0,   0,   0}, {  0,   0,   0}, {  0,   0,   0},
        {  0,   0,   0}, {  0,   0,   0}, {  0,   0,   0}, {  0,   0,   0}, {  0,   0,   0}, {  0,   0,   0 }, {  0,  0,  0 }, {  0,   0,   0}, {  0,   0,   0}, {  0,   0,   0}, {  0,   0,   0}, {  0,   0,   0},
        {  0,   0,   0}, {  0,   0,   0}, {  0,   0,   0}, {  0,   0,   0}, {  0,   0,   0},         {  0,   0,   0 },         {  0,   0,   0}, {  0,   0,   0}, {  0,   0,   0}, {  0,   0,   0}, {  0,   0,   0},
    },
    [_COLEMAK_DH] = {
        {  0,   0,   0}, {  0,   0,   0}, {  0,   0,   0}, {  0,   0,   0}, {  0,   0,   0}, {  0,   0,   0 }, {  0,  0,  0 }, {  0,   0,   0}, {  0,   0,   0}, {  0,   0,   0}, {  0,   0,   0}, {  0,   0,   0},
        {  0,   0,   0}, {  0,   0,   0}, {  0,   0,   0}, {  0,   0,   0}, {  0,   0,   0}, {  0,   0,   0 }, {  0,  0,  0 }, {  0,   0,   0}, {  0,   0,   0}, {  0,   0,   0}, {  0,   0,   0}, {  0,   0,   0},
        {  0,   0,   0}, {  0,   0,   0}, {  0,   0,   0}, {  0,   0,   0}, {  0,   0,   0}, {  0,   0,   0 }, {  0,  0,  0 }, {  0,   0,   0}, {  0,   0,   0}, {  0,   0,   0}, {  0,   0,   0}, {  0,   0,   0},
        {  0,   0,   0}, {  0,   0,   0}, {  0,   0,   0}, {  0,   0,   0}, {  0,   0,   0},         {  0,   0,   0 },         {  0,   0,   0}, {  0,   0,   0}, {  0,   0,   0}, {  0,   0,   0}, {  0,   0,   0},
    },
    /* Lower
     * ,-----------------------------------------------------------------------------------.
     * |   ~  |   !  |   @  |   #  |   $  |   %  |   ^  |   &  |   *  |   (  |   )  | Bksp |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * | Del  |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |   _  |   +  |   {  |   }  |  |   |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * |      |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |ISO ~ |ISO | | Home | End  |      |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * |      |      |      |      |      |             |      | Next | Vol- | Vol+ | Play |
     * `-----------------------------------------------------------------------------------'
     */
    [_LOWER] = {
        {  0,   0,   0}, { 69, 255, 255}, { 69, 255, 255}, { 69, 255, 255}, { 69, 255, 255}, { 69, 255, 255}, { 69, 255, 255}, { 69, 255, 255}, { 69, 255, 255}, { 69, 255, 255}, { 69, 255, 255}, {  0,   0,   0},
        {  0, 245, 245}, {152, 255, 255}, {152, 255, 255}, {152, 255, 255}, {152, 255, 255}, {152, 255, 255}, {152, 255, 255}, {  0,   0,   0}, {  0,   0,   0}, {  0,   0,   0}, {  0,   0,   0}, {  0,   0,   0},
        {  0,   0,   0}, {152, 255, 255}, {152, 255, 255}, {152, 255, 255}, {152, 255, 255}, {152, 255, 255}, {152, 255, 255}, {  0,   0,   0}, {  0,   0,   0}, {  0,   0,   0}, {  0,   0,   0}, {  0,   0,   0},
        {  0,   0,   0}, {  0,   0,   0}, {  0,   0,   0}, {  0,   0,   0}, {  0,   0,   0},          {  0,  0,  0 },          {  0,   0,   0}, {  0,   0,   0}, {  0,   0,   0}, {  0,   0,   0}, {  0,   0,   0},
    },
    [_RAISE] = {
        {  0,   0,   0}, {  0,   0,   0}, {  0,   0,   0}, {  0,   0,   0}, {  0,   0,   0}, {  0,   0,   0 }, {  0,  0,  0 }, {  0,   0,   0}, {  0,   0,   0}, {  0,   0,   0}, {  0,   0,   0}, {  0,   0,   0},
        {  0,   0,   0}, {  0,   0,   0}, {  0,   0,   0}, {  0,   0,   0}, {  0,   0,   0}, {  0,   0,   0 }, {  0,  0,  0 }, {  0,   0,   0}, {  0,   0,   0}, {  0,   0,   0}, {  0,   0,   0}, {  0,   0,   0},
        {  0,   0,   0}, {  0,   0,   0}, {  0,   0,   0}, {  0,   0,   0}, {  0,   0,   0}, {  0,   0,   0 }, {  0,  0,  0 }, {  0,   0,   0}, {  0,   0,   0}, {  0,   0,   0}, {  0,   0,   0}, {  0,   0,   0},
        {  0,   0,   0}, {  0,   0,   0}, {  0,   0,   0}, {  0,   0,   0}, {  0,   0,   0},         {  0,   0,   0 },         {  0,   0,   0}, {  0,   0,   0}, {  0,   0,   0}, {  0,   0,   0}, {  0,   0,   0},
    },
    [_ADJUST] = {
        {  0,   0,   0}, {  0,   0,   0}, {  0,   0,   0}, {  0,   0,   0}, {  0,   0,   0}, {  0,   0,   0 }, {  0,  0,  0 }, {  0,   0,   0}, {  0,   0,   0}, {  0,   0,   0}, {  0,   0,   0}, {  0,   0,   0},
        {  0,   0,   0}, {  0,   0,   0}, {  0,   0,   0}, {  0,   0,   0}, {  0,   0,   0}, {  0,   0,   0 }, {  0,  0,  0 }, {  0,   0,   0}, {  0,   0,   0}, {  0,   0,   0}, {  0,   0,   0}, {  0,   0,   0},
        {  0,   0,   0}, {  0,   0,   0}, {  0,   0,   0}, {  0,   0,   0}, {  0,   0,   0}, {  0,   0,   0 }, {  0,  0,  0 }, {  0,   0,   0}, {  0,   0,   0}, {  0,   0,   0}, {  0,   0,   0}, {  0,   0,   0},
        {  0,   0,   0}, {  0,   0,   0}, {  0,   0,   0}, {  0,   0,   0}, {  0,   0,   0},         {  0,   0,   0 },         {  0,   0,   0}, {  0,   0,   0}, {  0,   0,   0}, {  0,   0,   0}, {  0,   0,   0},
    },
};

void keyboard_post_init_user(void) {
  rgb_matrix_enable();
}

void set_layer_color(int layer) {
    for (int i = 0; i < DRIVER_LED_TOTAL; i++) {
        HSV hsv = {
            .h = pgm_read_byte(&ledmaps[layer][i][0]),
            .s = pgm_read_byte(&ledmaps[layer][i][1]),
            .v = pgm_read_byte(&ledmaps[layer][i][2]),
        };

        // Let undefined (value == 0) leds be unaffected
        if (!hsv.v) {
            continue;
        }

        if (!hsv.h && !hsv.s && !hsv.v) {
            rgb_matrix_set_color(i, 0, 0, 0);
        } else {
            RGB rgb = hsv_to_rgb( hsv );
            float f = (float)rgb_matrix_config.hsv.v / UINT8_MAX;
            rgb_matrix_set_color(i, f * rgb.r, f * rgb.g, f * rgb.b);
        }
    }
}

void rgb_matrix_indicators_user(void) {
    // if (keyboard_config.disable_layer_led) { return; }

    uint8_t layer = biton32(layer_state);

    switch (layer) {
        case 0 ... 5:
            set_layer_color(layer);
            break;
        default:
            if (rgb_matrix_get_flags() == LED_FLAG_NONE)
                rgb_matrix_set_color_all(0, 0, 0);
            break;
    }
}

// Layer logic

layer_state_t layer_state_set_user(layer_state_t state) {
    return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case QWERTY:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_QWERTY);
            }
            return false;
            break;
        case COLEMAK_DH:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_COLEMAK_DH);
            }
            return false;
            break;
        case BACKLIT:
            if (record->event.pressed) {
                register_code(KC_RSFT);
                #ifdef BACKLIGHT_ENABLE
                backlight_step();
                #endif
            } else {
                unregister_code(KC_RSFT);
            }
            return false;
            break;
    }
    return true;
}

bool     muse_mode      = false;
uint8_t  last_muse_note = 0;
uint16_t muse_counter   = 0;
uint8_t  muse_offset    = 70;
uint16_t muse_tempo     = 50;

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (muse_mode) {
        if (IS_LAYER_ON(_RAISE)) {
            if (clockwise) {
                muse_offset++;
            } else {
                muse_offset--;
            }
        } else {
            if (clockwise) {
                muse_tempo++;
            } else {
                muse_tempo--;
            }
        }
    } else {
        if (clockwise) {
            #ifdef MOUSEKEY_ENABLE
            tap_code(KC_MS_WH_DOWN);
            #else
            tap_code(KC_PGDN);
            #endif
        } else {
            #ifdef MOUSEKEY_ENABLE
            tap_code(KC_MS_WH_UP);
            #else
            tap_code(KC_PGUP);
            #endif
        }
    }
    return true;
}

bool dip_switch_update_user(uint8_t index, bool active) {
    switch (index) {
        case 0: {
            if (active) {
                layer_on(_ADJUST);
            } else {
                layer_off(_ADJUST);
            }
            break;
        }
        case 1:
            if (active) {
                muse_mode = true;
            } else {
                muse_mode = false;
            }
    }
    return true;
}

void matrix_scan_user(void) {
#ifdef AUDIO_ENABLE
    if (muse_mode) {
        if (muse_counter == 0) {
            uint8_t muse_note = muse_offset + SCALE[muse_clock_pulse()];
            if (muse_note != last_muse_note) {
                stop_note(compute_freq_for_midi_note(last_muse_note));
                play_note(compute_freq_for_midi_note(muse_note), 0xF);
                last_muse_note = muse_note;
            }
        }
        muse_counter = (muse_counter + 1) % muse_tempo;
    } else {
        if (muse_counter) {
            stop_all_notes();
            muse_counter = 0;
        }
    }
#endif
}

bool music_mask_user(uint16_t keycode) {
    switch (keycode) {
        case RAISE:
        case LOWER:
            return false;
        default:
            return true;
    }
}
