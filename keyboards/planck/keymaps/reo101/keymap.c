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

#include "action.h"
#include "action_layer.h"
#include "timer.h"
#include QMK_KEYBOARD_H
#include "muse.h"
#include "eeprom.h"

enum planck_layers {
    _QWERTY,
    _COLEMAK_DH,
    _LOWER,
    _RAISE,
    _ADJUST,
    _FKEYS,
};

enum planck_keycodes {
    QWERTY = SAFE_RANGE,
    COLEMAK_DH,
    BACKLIT,
};

#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)

#define BTR_ESC MT(MOD_LCTL, KC_ESCAPE)
#define BTR_ENT MT(MOD_RSFT, KC_ENTER)

// #define BTR_FN MT(MO(_FKEYS), OSL(_FKEYS))
#define BTR_FN TT(_FKEYS)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    /* Qwerty
     * ,-----------------------------------------------------------------------------------.
     * | Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Bksp |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * | Esc  |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |  '   |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |Enter |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * |  Fn  | Ctrl | GUI  | Alt  |Lower |    Space    |Raise | Left | Down |  Up  |Right |
     * `-----------------------------------------------------------------------------------'
     */
    [_QWERTY] = LAYOUT_planck_grid(
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
        BTR_ESC, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, BTR_ENT,
        BTR_FN,  KC_LCTL, KC_LGUI, KC_LALT, LOWER,   KC_SPC,  KC_SPC,  RAISE,   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT
    ),

    /* Colemak DH
     * ,-----------------------------------------------------------------------------------.
     * | Tab  |   Q  |   W  |   F  |   P  |   G  |   J  |   L  |   U  |   Y  |   ;  | Bksp |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * | Esc  |   A  |   R  |   S  |   T  |   V  |   M  |   N  |   E  |   I  |   O  |  '   |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * | Shift|   Z  |   X  |   C  |   D  |   B  |   K  |   H  |   ,  |   .  |   /  |Enter |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * |  Fn  | Ctrl | GUI  | Alt  |Lower |    Space    |Raise | Left | Down |  Up  |Right |
     * `-----------------------------------------------------------------------------------'
     */
    [_COLEMAK_DH] = LAYOUT_planck_grid(
        KC_TAB,  KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,    KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN, KC_BSPC,
        KC_ESC,  KC_A,    KC_R,    KC_S,    KC_T,    KC_V,    KC_M,    KC_N,    KC_E,    KC_I,    KC_O,    KC_QUOT,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_D,    KC_B,    KC_K,    KC_H,    KC_COMM, KC_DOT,  KC_SLSH, KC_ENT ,
        BTR_FN,  KC_LCTL, KC_LGUI, KC_LALT, LOWER,   KC_SPC,  KC_SPC,  RAISE,   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT
    ),

    /* Lower
     * ,-----------------------------------------------------------------------------------.
     * |   ~  |   !  |   @  |   #  |   $  |   %  |   ^  |   &  |   *  |   -  |   =  | Bksp |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * | Del  |   <  |   {  |   [  |   (  |   \  |   /  |   )  |   ]  |   }  |   >  |      |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * |      |      |      |      |   -  |      |      |   =  |      |      |      |      |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * |      |      |      |      |      |             |      | Next | Vol- | Vol+ | Play |
     * `-----------------------------------------------------------------------------------'
     */
    [_LOWER] = LAYOUT_planck_grid(
        KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_MINS, KC_EQL,  KC_BSPC,
        KC_DEL,  KC_LABK, KC_LCBR, KC_LBRC, KC_LPRN, KC_BSLS, KC_SLSH, KC_RPRN, KC_RBRC, KC_RCBR, KC_RABK, _______,
        _______, _______, _______, _______, KC_MINS, _______, _______, KC_EQL,  _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY
    ),

    /* Raise
     * ,-----------------------------------------------------------------------------------.
     * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Bksp |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * | Del  |      |      | Home |  End |   |  |   ?  | Pg Up| Pg Dn|      |      |      |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * |      |      |      |      |   _  |      |      |   +  |      |      |      |      |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * |      |      |      |      |      |             |      |      |      |      |      |
     * `-----------------------------------------------------------------------------------'
     */
    [_RAISE] = LAYOUT_planck_grid(
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
        KC_DEL,  _______, _______, KC_HOME, KC_END,  KC_PIPE, KC_QUES, KC_PGDN, KC_PGUP, _______, _______, _______,
        _______, _______, _______, _______, KC_UNDS, _______,_______,  KC_PLUS, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),

    /* Adjust (Lower + Raise)
     *                      v------------------------RGB CONTROL--------------------v
     * ,-----------------------------------------------------------------------------------.
     * |      |Reset |Debug | RGB  |RGBMOD| HUE+ | HUE- | SAT+ | SAT- |BRGTH+|BRGTH-|  Del |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * |      |      |MUSmod|Aud on|Audoff|AGnorm|AGswap|Qwerty|Colemk|      |      |      |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * |      |Voice-|Voice+|Mus on|Musoff|MIDIon|MIDIof|      |      |      |      |      |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * |      |      |      |      |      |             |      |      |      |      |      |
     * `-----------------------------------------------------------------------------------'
     */
    [_ADJUST] = LAYOUT_planck_grid(
        _______, QK_BOOT, _______, RGB_TOG, RGB_MOD, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD,    RGB_VAI, RGB_VAD, KC_DEL ,
        _______, _______, _______, AU_ON,   AU_OFF,  AG_NORM, AG_SWAP, QWERTY,  COLEMAK_DH, _______, _______, _______,
        _______, _______, _______, MU_ON,   MU_OFF,  MI_ON,   MI_OFF,  _______, _______,    _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______,    _______, _______, _______
    ),

    /* Function Keys
     * ,------------------------------------------------------------------------------------.
     * |      |      |      |      |      |       |      |      |      |      |      |      |
     * |------+------+------+------+------+-------+------+------+------+------+------+------|
     * |  F1  |  F2  |  F3  |  F4  |  F5   |  F6  |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |
     * |------+------+------+------+------+-------+------+------+------+------+------+------|
     * | F13  | F14  | F15  | F16  | F17   | F18  | F19  | F20  | F21  |  F22 |  F23 |  F24 |
     * |------+------+------+------+------+-------+------+------+------+------+------+------|
     * |  Fn  |      |      |      |   ⇩  |              |   ⇩  |      |      |      |      |
     * `------------------------------------------------------------------------------------'
     */
    [_FKEYS] = LAYOUT_planck_grid(
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,
        KC_F13,  KC_F14,  KC_F15,  KC_F16,  KC_F17,  KC_F18,  KC_F19,  KC_F20,  KC_F21,  KC_F22,  KC_F23,  KC_F24,
        BTR_FN,  XXXXXXX, XXXXXXX, XXXXXXX, LOWER,   XXXXXXX, XXXXXXX, RAISE,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
    ),
};

// RGB Lighting

rgb_config_t rgb_matrix_config;

#undef HSV_COLOURS
#define HSV_COLOURS

#ifndef HSV_COLOURS
#    define RGB_ROMAN_LEAF   0x55, 0xCB, 0x9E
#    define RGB_LIGHT_RED    0x00, 0xB7, 0xEE
#    define RGB_GREENY       0x59, 0xFF, 0x59
#    define RGB_LIGHT_PURPLE 0xF9, 0xE4, 0xFF
#    define RGB_LIGHT_BLUE   0x8D, 0xFF, 0xE9
#    define RGB_GREEN1       0x00, 0xFF, 0x00
#    define RGB_GREEN2       0x0B, 0xFF, 0x0B
#    define RGB_GREEN3       0x16, 0xFF, 0x16
#    define RGB_GREEN4       0x22, 0xFF, 0x22
#    define RGB_GREEN5       0x2D, 0xFF, 0x2D
#    define RGB_GREEN6       0x38, 0xFF, 0x38
#    define RGB_AZURY        0x1E, 0xCB, 0xE1
#    define RGB_PORTO        0xC3, 0x7A, 0x3C
#else
#    define HSV_GREENY       180, 73, 100
// #    define HSV_AZURY        187, 87, 88
// #    define HSV_PORTO        28,  69, 76
#    define HSV_AZURY        133, 220, 225
#    define HSV_PORTO        19,  176, 195
#    define HSV_PTL_B        154, 255, 255
#    define HSV_PTL_O        23,  255, 255
#    define HSV_ORANG1       20,  255, 255
#    define HSV_ORANG2       40,  255, 255
#    define HSV_ORANG3       60,  255, 255
#    define HSV_ORANG4       80,  255, 255
#    define HSV_ORANG5       100, 255, 255
#    define HSV_ORANG6       120, 255, 255
#    define HSV_ORANG7       140, 255, 255
#    define HSV_ORANG8       160, 255, 255
#    define HSV_ORANG9       180, 255, 255
#    define HSV_ORANG0       200, 255, 255

#endif

uint8_t PROGMEM ledmaps[][RGB_MATRIX_LED_COUNT][3] = {
    [_QWERTY] = {
        {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK},
        {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK},
        {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK},
        {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK},        {RGB_BLACK},       {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK},
    },
    [_COLEMAK_DH] = {
        {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK},
        {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK},
        {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK},
        {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK},        {RGB_BLACK},       {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK},
    },
    [_LOWER] = {
        {RGB_BLACK}, {HSV_ORANG1}, {HSV_ORANG2}, {HSV_ORANG3}, {HSV_ORANG4}, {HSV_ORANG5}, {HSV_ORANG6}, {HSV_ORANG7}, {HSV_ORANG8}, {HSV_ORANG9}, {HSV_ORANG0}, {HSV_RED},
        {HSV_RED},   {HSV_PTL_B},  {HSV_PTL_B},  {HSV_PTL_B},  {HSV_PTL_B},  {HSV_PTL_B},  {HSV_PTL_O},  {HSV_PTL_O},  {HSV_PTL_O},  {HSV_PTL_O},  {HSV_PTL_O},  {RGB_BLACK},
        {RGB_BLACK}, {RGB_BLACK},  {RGB_BLACK},  {RGB_BLACK},  {HSV_PTL_B},  {RGB_BLACK},  {RGB_BLACK},  {HSV_PTL_O},  {RGB_BLACK},  {RGB_BLACK},  {RGB_BLACK},  {RGB_BLACK},
        {RGB_BLACK}, {RGB_BLACK},  {RGB_BLACK},  {RGB_BLACK},  {RGB_BLACK},          {RGB_BLACK},        {RGB_BLACK},  {HSV_YELLOW}, {HSV_BLUE},   {HSV_RED},    {HSV_PURPLE},
    },
    [_RAISE] = {
        {RGB_BLACK}, {HSV_ORANG1}, {HSV_ORANG2}, {HSV_ORANG3}, {HSV_ORANG4}, {HSV_ORANG5}, {HSV_ORANG5}, {HSV_ORANG4}, {HSV_ORANG3}, {HSV_ORANG2}, {HSV_ORANG1}, {HSV_RED},
        {HSV_RED},   {RGB_BLACK},  {RGB_BLACK},  {HSV_RED},    {HSV_BLUE},   {HSV_PTL_B},  {HSV_PTL_O},  {HSV_RED},    {HSV_BLUE},   {RGB_BLACK},  {RGB_BLACK},  {RGB_BLACK},
        {RGB_BLACK}, {RGB_BLACK},  {RGB_BLACK},  {RGB_BLACK},  {HSV_PTL_B},  {RGB_BLACK},  {RGB_BLACK},  {HSV_PTL_O},  {RGB_BLACK},  {RGB_BLACK},  {RGB_BLACK},  {RGB_BLACK},
        {RGB_BLACK}, {RGB_BLACK},  {RGB_BLACK},  {RGB_BLACK},  {RGB_BLACK},          {RGB_BLACK},        {RGB_BLACK},  {RGB_BLACK},  {RGB_BLACK},  {RGB_BLACK},  {RGB_BLACK},
    },
    [_ADJUST] = {
        {RGB_BLACK}, {HSV_PURPLE}, {HSV_YELLOW}, {RGB_BLUE},  {RGB_CYAN},  {HSV_RED},    {HSV_BLUE},   {HSV_RED},   {HSV_BLUE},  {HSV_RED},   {HSV_BLUE},  {RGB_BLACK},
        {RGB_BLACK}, {RGB_BLACK},  {RGB_BLACK},  {HSV_BLUE},  {HSV_RED},   {HSV_YELLOW}, {HSV_YELLOW}, {HSV_GREEN}, {HSV_TEAL},  {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK},
        {RGB_BLACK}, {HSV_BLUE},   {HSV_RED},    {HSV_BLUE},  {HSV_RED},   {HSV_RED},    {HSV_BLUE},   {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK},
        {RGB_BLACK}, {RGB_BLACK},  {RGB_BLACK},  {RGB_BLACK}, {RGB_BLACK},         {RGB_BLACK},        {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK},
    },
    [_FKEYS] = {
        {RGB_BLACK}, {RGB_BLACK},  {RGB_BLACK},  {RGB_BLACK},  {RGB_BLACK},  {RGB_BLACK},  {RGB_BLACK},  {RGB_BLACK},  {RGB_BLACK},  {RGB_BLACK},  {RGB_BLACK},  {RGB_BLACK},
        {RGB_BLACK}, {HSV_ORANG1}, {HSV_ORANG2}, {HSV_ORANG3}, {HSV_ORANG4}, {HSV_ORANG5}, {HSV_ORANG5}, {HSV_ORANG4}, {HSV_ORANG3}, {HSV_ORANG2}, {HSV_ORANG1}, {RGB_BLACK},
        {RGB_BLACK}, {HSV_ORANG5}, {HSV_ORANG4}, {HSV_ORANG3}, {HSV_ORANG2}, {HSV_ORANG1}, {HSV_ORANG1}, {HSV_ORANG2}, {HSV_ORANG3}, {HSV_ORANG4}, {HSV_ORANG5},  {RGB_BLACK},
        {RGB_BLACK}, {RGB_BLACK},  {RGB_BLACK},  {RGB_BLACK},  {RGB_BLACK},          {RGB_BLACK},        {RGB_BLACK},  {RGB_BLACK},  {RGB_BLACK},  {RGB_BLACK},  {RGB_BLACK},
    },
};

void keyboard_post_init_user(void) {
    rgb_matrix_enable();
}

void set_layer_color(int layer) {
    for (int i = 0; i < RGB_MATRIX_LED_COUNT; i++) {
        #ifdef HSV_COLOURS
            HSV hsv = {
                .h = pgm_read_byte(&ledmaps[layer][i][0]),
                .s = pgm_read_byte(&ledmaps[layer][i][1]),
                .v = pgm_read_byte(&ledmaps[layer][i][2]),
            };
            RGB rgb = hsv_to_rgb_nocie(hsv);
        #else
            RGB rgb = {
                .r = pgm_read_byte(&ledmaps[layer][i][0]),
                .g = pgm_read_byte(&ledmaps[layer][i][1]),
                .b = pgm_read_byte(&ledmaps[layer][i][2]),
            };
            HSV hsv;
            {
                double r = rgb.r / 255.0,
                       g = rgb.g / 255.0,
                       b = rgb.b / 255.0;

                double min_c = (r < b) ? ((r < g) ? r : g) : ((b < g) ? b : g),
                       max_c = (r > b) ? ((r > g) ? r : g) : ((b > g) ? b : g);

                if (min_c == max_c) {
                    hsv.h = 0;
                    hsv.s = 0;
                    hsv.v = max_c;
                } else {
                    double s  = (max_c - min_c) / max_c,
                           h,
                           v = max_c,
                           rc = (max_c - r) / (max_c - min_c),
                           gc = (max_c - g) / (max_c - min_c),
                           bc = (max_c - b) / (max_c - min_c);

                    if (r == max_c) {
                        h = 0.0 + bc - gc;
                    } else if (g == max_c) {
                        h = 2.0 + rc - bc;
                    } else {
                        h = 4.0 + gc - rc;
                    }

                    hsv.h = h / 6;
                    hsv.s = s * 100;
                    hsv.v = v * 100;
                }
            }
        #endif

        // Let undefined (value == 0) leds be unaffected
        if (!hsv.v) {
            continue;
        }

        if (!hsv.h && !hsv.s && !hsv.v) {
            rgb_matrix_set_color(i, 0, 0, 0);
        } else {
            float f = (float)rgb_matrix_config.hsv.v / UINT8_MAX;
            rgb_matrix_set_color(i, f * rgb.r, f * rgb.g, f * rgb.b);
        }
    }
}

bool rgb_matrix_indicators_user(void) {
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

    return true;
}

// Layer logic

layer_state_t layer_state_set_user(layer_state_t state) {
    return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

uint8_t last_mode = UINT8_MAX;
uint16_t g_last_keycode;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    g_last_keycode = keycode;

    switch (keycode) {
        case QWERTY: {
            if (record->event.pressed) {
                set_single_persistent_default_layer(_QWERTY);
            }
            return false;
        }
        case COLEMAK_DH: {
            if (record->event.pressed) {
                set_single_persistent_default_layer(_COLEMAK_DH);
            }
            return false;
        }
        // case BACKLIT: {
        //     if (record->event.pressed) {
        //         register_code(KC_RSFT);
        //         #ifdef BACKLIGHT_ENABLE
        //         backlight_step();
        //         #endif
        //     } else {
        //         unregister_code(KC_RSFT);
        //     }
        //     return false;
        // }
        default: {
            return true;
        }
    }
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
