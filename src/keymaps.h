#ifndef _KEYMAP_H
#define _KEYMAP_H

#include <linux/uinput.h>
#include <stdint.h>

#define NROWS 4
#define NCOLS 8
#define KEY_UNDEFINED INT32_MAX
#define KEY_NUMMODE -1
#define KEY_CHANGE_MAP -2

// clang-format off
const int base_keymap[NROWS * NCOLS] = {
    KEY_ESC, KEY_W, KEY_E, KEY_T, KEY_U, KEY_I, KEY_O, KEY_BACKSPACE,
    KEY_CAPSLOCK, KEY_A, KEY_S, KEY_F, KEY_H, KEY_K, KEY_L, KEY_ENTER,
    KEY_NUMMODE, KEY_X, KEY_C, KEY_B, KEY_N, KEY_M, KEY_UP, KEY_CHANGE_MAP,
    KEY_LEFTCTRL, KEY_TAB, KEY_LEFTALT, KEY_SPACE, KEY_SPACE, KEY_LEFT, KEY_DOWN, KEY_RIGHT
};

const int base_keymap_dbl_keys[NROWS * NCOLS] = {
    KEY_UNDEFINED, KEY_Q, KEY_UNDEFINED, KEY_R, KEY_Y, KEY_UNDEFINED, KEY_P, KEY_UNDEFINED,
    KEY_UNDEFINED, KEY_UNDEFINED, KEY_D, KEY_G, KEY_J, KEY_UNDEFINED, KEY_UNDEFINED, KEY_UNDEFINED,
    KEY_UNDEFINED, KEY_Z, KEY_V, KEY_UNDEFINED, KEY_UNDEFINED, KEY_UNDEFINED, KEY_UNDEFINED, KEY_UNDEFINED,
    KEY_UNDEFINED, KEY_UNDEFINED, KEY_UNDEFINED, KEY_UNDEFINED, KEY_UNDEFINED, KEY_UNDEFINED, KEY_UNDEFINED, KEY_UNDEFINED
};

const int num_keymap[NROWS * NCOLS] = {
    KEY_UNDEFINED, KEY_UNDEFINED, KEY_1, KEY_2, KEY_3, KEY_MINUS, KEY_UNDEFINED, KEY_BACKSPACE,
    KEY_UNDEFINED, KEY_UNDEFINED, KEY_4, KEY_5, KEY_6, KEY_EQUAL, KEY_SEMICOLON, KEY_UNDEFINED,
    KEY_UNDEFINED, KEY_UNDEFINED, KEY_UNDEFINED, KEY_7, KEY_8, KEY_9, KEY_UNDEFINED, KEY_UNDEFINED,
    KEY_UNDEFINED, KEY_UNDEFINED, KEY_UNDEFINED, KEY_UNDEFINED, KEY_0, KEY_UNDEFINED, KEY_DOT, KEY_COMMA
};

const int num_keymap_shifted_keys[NROWS * NCOLS] = {
    KEY_UNDEFINED, KEY_2, KEY_UNDEFINED, KEY_UNDEFINED, KEY_UNDEFINED, KEY_UNDEFINED, KEY_EQUAL, KEY_UNDEFINED,
    KEY_UNDEFINED, KEY_1, KEY_UNDEFINED, KEY_UNDEFINED, KEY_UNDEFINED, KEY_UNDEFINED, KEY_UNDEFINED, KEY_UNDEFINED,
    KEY_UNDEFINED, KEY_UNDEFINED, KEY_UNDEFINED, KEY_UNDEFINED, KEY_UNDEFINED, KEY_UNDEFINED, KEY_UNDEFINED, KEY_UNDEFINED,
    KEY_UNDEFINED, KEY_UNDEFINED, KEY_UNDEFINED, KEY_SLASH, KEY_UNDEFINED, KEY_8, KEY_UNDEFINED, KEY_UNDEFINED
};

const int mouse_keymap[NROWS * NCOLS] = {
    KEY_UNDEFINED, KEY_UNDEFINED, KEY_UNDEFINED, KEY_UNDEFINED, KEY_UNDEFINED, KEY_UNDEFINED, KEY_UNDEFINED, KEY_UNDEFINED,
    KEY_UNDEFINED, KEY_UNDEFINED, KEY_UNDEFINED, KEY_UNDEFINED, KEY_UNDEFINED, KEY_UNDEFINED, KEY_UNDEFINED, KEY_UNDEFINED,
    KEY_UNDEFINED, KEY_UNDEFINED, KEY_UNDEFINED, KEY_UNDEFINED, KEY_UNDEFINED, KEY_UNDEFINED, KEY_UNDEFINED, KEY_UNDEFINED,
    KEY_UNDEFINED, KEY_UNDEFINED, KEY_UNDEFINED, KEY_UNDEFINED, KEY_UNDEFINED, KEY_UNDEFINED, KEY_UNDEFINED, KEY_UNDEFINED
};
// clang-format on

const char *keycode_to_string(int keycode) {
  switch (keycode) {
  case KEY_ESC:
    return "KEY_ESC";
  case KEY_W:
    return "KEY_W";
  case KEY_E:
    return "KEY_E";
  case KEY_T:
    return "KEY_T";
  case KEY_U:
    return "KEY_U";
  case KEY_I:
    return "KEY_I";
  case KEY_O:
    return "KEY_O";
  case KEY_BACKSPACE:
    return "KEY_BACKSPACE";
  case KEY_CAPSLOCK:
    return "KEY_CAPSLOCK";
  case KEY_A:
    return "KEY_A";
  case KEY_S:
    return "KEY_S";
  case KEY_F:
    return "KEY_F";
  case KEY_H:
    return "KEY_H";
  case KEY_K:
    return "KEY_K";
  case KEY_L:
    return "KEY_L";
  case KEY_ENTER:
    return "KEY_ENTER";
  case KEY_NUMMODE:
    return "KEY_NUMMODE";
  case KEY_X:
    return "KEY_X";
  case KEY_C:
    return "KEY_C";
  case KEY_B:
    return "KEY_B";
  case KEY_N:
    return "KEY_N";
  case KEY_M:
    return "KEY_M";
  case KEY_UP:
    return "KEY_UP";
  case KEY_CHANGE_MAP:
    return "KEY_CHANGE_MAP";
  case KEY_LEFTCTRL:
    return "KEY_LEFTCTRL";
  case KEY_TAB:
    return "KEY_TAB";
  case KEY_LEFTALT:
    return "KEY_LEFTALT";
  case KEY_SPACE:
    return "KEY_SPACE";
  case KEY_LEFT:
    return "KEY_LEFT";
  case KEY_DOWN:
    return "KEY_DOWN";
  case KEY_RIGHT:
    return "KEY_RIGHT";
  case KEY_UNDEFINED:
    return "KEY_UNDEFINED";
  case KEY_Q:
    return "KEY_Q";
  case KEY_Y:
    return "KEY_Y";
  case KEY_P:
    return "KEY_P";
  case KEY_SEMICOLON:
    return "KEY_SEMICOLON";
  case KEY_Z:
    return "KEY_Z";
  case KEY_V:
    return "KEY_V";
  case KEY_DOT:
    return "KEY_DOT";
  case KEY_COMMA:
    return "KEY_COMMA";
  case KEY_SLASH:
    return "KEY_SLASH";
  case KEY_1:
    return "KEY_1";
  case KEY_2:
    return "KEY_2";
  case KEY_3:
    return "KEY_3";
  case KEY_4:
    return "KEY_4";
  case KEY_5:
    return "KEY_5";
  case KEY_6:
    return "KEY_6";
  case KEY_7:
    return "KEY_7";
  case KEY_8:
    return "KEY_8";
  case KEY_9:
    return "KEY_9";
  case KEY_0:
    return "KEY_0";
  case KEY_MINUS:
    return "KEY_MINUS";
  case KEY_EQUAL:
    return "KEY_EQUAL";
  case KEY_D:
    return "KEY_D";
  case KEY_R:
    return "KEY_R";
  default:
    return "UNKNOWN_KEYCODE";
  }
}

#define KEYMAP_BASE 0
#define KEYMAP_NUM 1
#endif
