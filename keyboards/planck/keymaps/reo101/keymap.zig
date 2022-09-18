const std = @import("std");
const c = @cImport({
    @cDefine("MATRIX_ROWS", "8");
    @cDefine("MATRIX_COLS", "6");
    @cInclude("config.h");
    @cInclude("keycode.h");
    @cInclude("keymap.h");
});
const layout = @import("layout.zig").layout;

const custom_layers = enum(u32) {
    _QWERTY,
    _COLEMAK_DH,
    _LOWER,
    _RAISE,
    _ADJUST,
};

const custom_keycodes = enum(u32) {
    QWERTY = @as(u32, c.SAFE_RANGE),
    COLEMAK_DH,
    BACKLIT,
};

const _QWERTY = 0;
const _LOWER = 1;
const _RAISE = 2;
const _ADJUST = 3;

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
