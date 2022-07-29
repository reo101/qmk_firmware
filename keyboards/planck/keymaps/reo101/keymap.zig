const std = @import("std");
const c = @cImport({
    @cInclude("config.h");
    @cInclude("keycode.h");
    @cInclude("keymap.h");
    // @cDefine("LOWER", c.MO(c._LOWER));
    // @cDefine("RAISE", c.MO(c._RAISE));
});

const custom_layers = enum(u32) {
    _QWERTY,
    _COLEMAK,
    _COLEMAK_DH,
    _DVORAK,
    _LOWER,
    _RAISE,
    _ADJUST,
};

const custom_keycodes = enum(u32) {
    QWERTY = @as(u32, c.SAFE_RANGE),
    LOWER,
    RAISE,
    ADJUST,
};

const _QWERTY = 0;
const _LOWER = 1;
const _RAISE = 2;
const _ADJUST = 3;

// zig fmt: off
fn layout(comptime T: type,
          segments: comptime_int,
          rows: comptime_int,
          cols: comptime_int,
          reverse_last: bool,
          keys: [segments * rows * cols]T,
         ) [segments * rows][cols]T {
    var result: [segments * rows][cols]T = undefined;

    var row: u8 = 0;
    var segment: u8 = undefined;
    while (row < rows) : (row += 1) {
        segment = 0;
        while (segment < segments) : (segment += 1) {
            std.mem.copy(T, result[rows * segment + row][0..],
                            keys[((row * 2) + segment)     * cols ..
                                 ((row * 2) + segment + 1) * cols]);
        }
        if (reverse_last and segment != 0) {
            // Reverse last segment (if wanted)
            std.mem.reverse(T, result[rows * (segment - 1) + row][0..]);
        }
    }

    return result;
}
// zig fmt: on

pub export const keymaps = keymaps: {
    const segments = 2;
    const rows = 4;
    const cols = 6;

    const layouts = 4;

    var _keymaps: [layouts][segments * rows][cols]c_int = [_][segments * rows][cols]c_int{undefined} ** layouts;

    // zig fmt: off
    // Qwerty
    // ,-----------------------------------------------------------------------------------.
    // | Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Bksp |
    // |------+------+------+------+------+------+------+------+------+------+------+------|
    // | Esc  |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |  '   |
    // |------+------+------+------+------+------+------+------+------+------+------+------|
    // | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |Enter |
    // |------+------+------+------+------+------+------+------+------+------+------+------|
    // | Brite| Ctrl | Alt  | GUI  |Lower |    Space    |Raise | Left | Down |  Up  |Right |
    // `-----------------------------------------------------------------------------------'
    //
    _keymaps[_QWERTY] = layout(c_int, segments, rows, cols, false, .{
        c.KC_TAB,  c.KC_Q,    c.KC_W,    c.KC_E,    c.KC_R,    c.KC_T,    c.KC_Y,    c.KC_U,    c.KC_I,    c.KC_O,    c.KC_P,    c.KC_BSPC,
        c.KC_ESC,  c.KC_A,    c.KC_S,    c.KC_D,    c.KC_F,    c.KC_G,    c.KC_H,    c.KC_J,    c.KC_K,    c.KC_L,    c.KC_SCLN, c.KC_QUOT,
        c.KC_LSFT, c.KC_Z,    c.KC_X,    c.KC_C,    c.KC_V,    c.KC_B,    c.KC_N,    c.KC_M,    c.KC_COMM, c.KC_DOT,  c.KC_SLSH, c.KC_ENT ,
        c.KC_NO,   c.KC_LCTL, c.KC_LALT, c.KC_LGUI, c.KC_NO,   c.KC_SPC,  c.KC_SPC,  c.KC_NO,   c.KC_LEFT, c.KC_DOWN, c.KC_UP,   c.KC_RGHT,
    });
    // zig fmt: on

    break :keymaps _keymaps;
};

test "layout() works" {
    const ElemType: type = [:0]const u8;

    const SEGMENTS = 2;
    const ROWS = 5;
    const COLS = 6;

    const src = [SEGMENTS * ROWS * COLS]ElemType{
        "LA1", "LA2", "LA3", "LA4", "LA5", "LA6", "RA6", "RA5", "RA4", "RA3", "RA2", "RA1",
        "LB1", "LB2", "LB3", "LB4", "LB5", "LB6", "RB6", "RB5", "RB4", "RB3", "RB2", "RB1",
        "LC1", "LC2", "LC3", "LC4", "LC5", "LC6", "RC6", "RC5", "RC4", "RC3", "RC2", "RC1",
        "LD1", "LD2", "LD3", "LD4", "LD5", "LD6", "RD6", "RD5", "RD4", "RD3", "RD2", "RD1",
        "_NO", "_NO", "LE3", "LE4", "LE5", "LE6", "RE6", "RE5", "RE4", "RE3", "_NO", "_NO",
    };

    const expected = [SEGMENTS * ROWS][COLS]ElemType{
        .{ "LA1", "LA2", "LA3", "LA4", "LA5", "LA6" },
        .{ "LB1", "LB2", "LB3", "LB4", "LB5", "LB6" },
        .{ "LC1", "LC2", "LC3", "LC4", "LC5", "LC6" },
        .{ "LD1", "LD2", "LD3", "LD4", "LD5", "LD6" },
        .{ "_NO", "_NO", "LE3", "LE4", "LE5", "LE6" },

        .{ "RA1", "RA2", "RA3", "RA4", "RA5", "RA6" },
        .{ "RB1", "RB2", "RB3", "RB4", "RB5", "RB6" },
        .{ "RC1", "RC2", "RC3", "RC4", "RC5", "RC6" },
        .{ "RD1", "RD2", "RD3", "RD4", "RD5", "RD6" },
        .{ "_NO", "_NO", "RE3", "RE4", "RE5", "RE6" },
    };

    const actual = layout(ElemType, SEGMENTS, ROWS, COLS, true, src);

    // std.debug.print(
    //     "src: {s}\nexpected: {s}\actual: {s}\n\n",
    //     .{
    //         src,
    //         expected,
    //         actual,
    //     },
    // );

    try std.testing.expectEqual(expected, actual);
}

// .{ "LA1", "LA2", "LA3", "LA4", "LA5", "LA6"},
// .{ "LB1", "LB2", "LB3", "LB4", "LB5", "LB6"},
// .{ "LC1", "LC2", "LC3", "LC4", "LC5", "LC6"},
// .{ "LD1", "LD2", "LD3", "LD4", "LD5", "LD6"},
// .{ "KC_NO", "KC_NO", "LE3", "LE4", "LE5", "LE6"},
// .{ "RA1", "RA2", "RA3", "RA4", "RA5", "RA6"},
// .{ "RB1", "RB2", "RB3", "RB4", "RB5", "RB6"},
// .{ "RC1", "RC2", "RC3", "RC4", "RC5", "RC6"},
// .{ "RD1", "RD2", "RD3", "RD4", "RD5", "RD6"},
// .{ "KC_NO", "KC_NO", "RE3", "RE4", "RE5", "RE6"},

// #define LAYOUT( \
//     LA1, LA2, LA3, LA4, LA5, LA6,           RA6, RA5, RA4, RA3, RA2, RA1, \
//     LB1, LB2, LB3, LB4, LB5, LB6,           RB6, RB5, RB4, RB3, RB2, RB1, \
//     LC1, LC2, LC3, LC4, LC5, LC6,           RC6, RC5, RC4, RC3, RC2, RC1, \
//     LD1, LD2, LD3, LD4, LD5, LD6, LE6, RE6, RD6, RD5, RD4, RD3, RD2, RD1, \
//                         LE3, LE4, LE5, RE5, RE4, RE3 \
//     ) \
//     { \
//         { LA1, LA2, LA3, LA4, LA5, LA6 }, \
//         { LB1, LB2, LB3, LB4, LB5, LB6 }, \
//         { LC1, LC2, LC3, LC4, LC5, LC6 }, \
//         { LD1, LD2, LD3, LD4, LD5, LD6 }, \
//         { KC_NO, KC_NO, LE3, LE4, LE5, LE6 }, \
//         { RA1, RA2, RA3, RA4, RA5, RA6 }, \
//         { RB1, RB2, RB3, RB4, RB5, RB6 }, \
//         { RC1, RC2, RC3, RC4, RC5, RC6 }, \
//         { RD1, RD2, RD3, RD4, RD5, RD6 }, \
//         { KC_NO, KC_NO, RE3, RE4, RE5, RE6 } \
//     }

// extern const keymaps = [MATRIX_COLS][MATRIX_ROWS][]u16{
//     // _QWERTY
//     [MATRIX_ROWS][_]u16{
//         // Left
//         [MATRIX_ROWS]u16{ KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5 },
//         [MATRIX_ROWS]u16{ KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T },
//         [MATRIX_ROWS]u16{ KC_LCTL, KC_A, KC_S, KC_D, KC_4, KC_G },
//         [MATRIX_ROWS]u16{ KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B },
//         [MATRIX_ROWS]u16{ KC_NO, KC_NO, KC_LGUI, LOWER, KC_ENT, KC_HOME },
//         // Right
//         [MATRIX_ROWS]u16{ KC_BSPC, KC_0, KC_9, KC_8, KC_7, KC_6 },
//         [MATRIX_ROWS]u16{ KC_DEL, KC_P, KC_O, KC_I, KC_U, KC_Y },
//         [MATRIX_ROWS]u16{ KC_QUOT, KC_SCLN, KC_L, KC_K, KC_J, KC_H },
//         [MATRIX_ROWS]u16{ KC_RSFT, KC_SLSH, KC_DOT, KC_COMM, KC_M, KC_N },
//         [MATRIX_ROWS]u16{ KC_NO, KC_NO, KC_RALT, RAISE, KC_SPC, KC_END },
//     },
//     [MATRIX_ROWS][_]u16{},
// };
