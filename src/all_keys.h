#ifndef _ALL_KEYS_H
#define _ALL_KEYS_H

#include <linux/uinput.h>

int ALL_KEYS[][2] = {
    {KEY_ESC, 0x01},     {KEY_W, 0x11},         {KEY_E, 0x12},
    {KEY_T, 0x14},       {KEY_U, 0x16},         {KEY_I, 0x17},
    {KEY_O, 0x18},       {KEY_BACKSPACE, 0x0e}, {KEY_CAPSLOCK, 0x3a},
    {KEY_A, 0x1e},       {KEY_S, 0x1f},         {KEY_F, 0x21},
    {KEY_H, 0x23},       {KEY_K, 0x25},         {KEY_L, 0x26},
    {KEY_ENTER, 0x1c},   {KEY_X, 0x2d},         {KEY_C, 0x2e},
    {KEY_B, 0x30},       {KEY_N, 0x31},         {KEY_M, 0x32},
    {KEY_UP, 0xc8},      {KEY_LEFTCTRL, 0x1d},  {KEY_TAB, 0x0f},
    {KEY_LEFTALT, 0x38}, {KEY_SPACE, 0x39},     {KEY_LEFT, 0xcb},
    {KEY_DOWN, 0xd0},    {KEY_RIGHT, 0xcd},     {KEY_Q, 0x10},
    {KEY_R, 0x13},       {KEY_Y, 0x15},         {KEY_P, 0x19},
    {KEY_D, 0x20},       {KEY_G, 0x22},         {KEY_J, 0x24},
    {KEY_Z, 0x2c},       {KEY_V, 0x2f},         {KEY_1, 0x02},
    {KEY_2, 0x03},       {KEY_3, 0x04},         {KEY_MINUS, 0x0c},
    {KEY_4, 0x05},       {KEY_5, 0x06},         {KEY_6, 0x07},
    {KEY_EQUAL, 0x0d},   {KEY_SEMICOLON, 0x27}, {KEY_LEFTSHIFT, 0x2a},
    {KEY_7, 0x08},       {KEY_8, 0x09},         {KEY_9, 0x0a},
    {KEY_0, 0x0b},       {KEY_DOT, 0x34},       {KEY_COMMA, 0x33},
    {KEY_SLASH, 0x35},   {KEY_LEFTBRACE, 0x1a}, {KEY_RIGHTBRACE, 0x1b}};

#define ALL_KEYS_LENGTH sizeof(ALL_KEYS) / sizeof(*ALL_KEYS)

int get_key_scancode(int code) {
  for (int i = 0; i < ALL_KEYS_LENGTH; i++) {
    if (ALL_KEYS[i][0] == code)
      return ALL_KEYS[i][1];
  }

  return -1;
}

#endif
