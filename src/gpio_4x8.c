#include <fcntl.h>
#include <linux/uinput.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>

#include "all_keys.h"
#include "keymaps.h"
#include "rpi_gpio.h"

#define UINPUT_DEV_NAME "edu_keyboard"

const int cols[NCOLS] = {12, 16, 20, 21, 14, 15, 23, 7};
const int rows[NROWS] = {17, 4, 3, 2};

long long millis(void) {
  struct timeval tv;

  gettimeofday(&tv, NULL);
  return (((long long)tv.tv_sec) * 1000) + (tv.tv_usec / 1000);
}

int uinput_init() {
  struct uinput_setup usetup;
  int fd = open("/dev/uinput", O_WRONLY | O_NONBLOCK);
  if (fd < 0)
    return -1;
  ioctl(fd, UI_SET_EVBIT, EV_KEY);
  ioctl(fd, UI_SET_EVBIT, EV_REP);
  for (int i = 0; i < ALL_KEYS_LENGTH; i++) {
    ioctl(fd, UI_SET_KEYBIT, ALL_KEYS[i][0]);
  }
  memset(&usetup, 0, sizeof(usetup));
  usetup.id.bustype = BUS_USB;
  usetup.id.vendor = 0x1209; // Generic
  usetup.id.product = 0x7501;
  strcpy(usetup.name, UINPUT_DEV_NAME);
  ioctl(fd, UI_DEV_SETUP, &usetup);
  ioctl(fd, UI_DEV_CREATE);
  return fd;
}

void uinput_emit(int fd, int type, int code, int val) {
  struct input_event ie;
  ie.type = type;
  ie.code = code;
  ie.value = val;
  ie.time.tv_sec = 0;
  ie.time.tv_usec = 0;
  write(fd, &ie, sizeof(ie));
}

long long last_presses[NROWS * NCOLS] = {0};

int setup() {
  int uinput_fd = uinput_init();
  if (uinput_fd < 0) {
    perror("Failed to initialize UInput");
    exit(1);
  }
  if (rpi_gpio_init() < 0) {
    perror("Failed to initialize RPi GPIO");
    exit(1);
  }
  for (int i = 0; i < NROWS; i++) {
    rpi_gpio_setup(rows[i], INPUT, PUD_OFF);
  }
  for (int i = 0; i < NCOLS; i++) {
    rpi_gpio_setup(cols[i], INPUT, PUD_UP);
  }

  return uinput_fd;
}

int current_keymap = KEYMAP_BASE;
int is_num_mode = 0;
int last_keycode = -1;
long long last_key_pressed_at = 0;
int key_delay_threshold = 100;
int last_key_release_handled = 0;

typedef struct emitted_t {
  int code;
  int shifted;
} Emitted;

void emit_key(int fd, int code, int state) {
  int scancode = get_key_scancode(code);
  if (scancode == -1)
    return;
  uinput_emit(fd, EV_MSC, MSC_SCAN, scancode);
  usleep(200);
  uinput_emit(fd, EV_KEY, code, state);
  usleep(1000);
  uinput_emit(fd, EV_SYN, SYN_REPORT, 0);
}

void emit_combined_key(int fd, int wrapper, int code) {
  emit_key(fd, wrapper, 1);
  usleep(500);
  emit_key(fd, code, 1);
  usleep(500);
  emit_key(fd, code, 0);
  usleep(100);
  emit_key(fd, wrapper, 0);
}

int in_ctrl_comb = 0;

Emitted handle_key(int fd, int keycode, int is_long_press) {
  Emitted e = {.code = 0, .shifted = 0};

  if (base_keymap[keycode] == KEY_NUMMODE) {
    current_keymap = (current_keymap == KEYMAP_NUM) ? KEYMAP_BASE : KEYMAP_NUM;
    e.code = -1;
    return e;
  }

  switch (current_keymap) {
  case KEYMAP_NUM:
    if (num_keymap[keycode] != KEY_UNDEFINED) {
      e.code = num_keymap[keycode];
    } else if (num_keymap[keycode] == KEY_UNDEFINED &&
               num_keymap_shifted_keys[keycode] != KEY_UNDEFINED) {
      e.shifted = 1;
      e.code = num_keymap_shifted_keys[keycode];
    }
    break;

  default:
    e.code = (is_long_press && base_keymap_dbl_keys[keycode] != KEY_UNDEFINED)
                 ? base_keymap_dbl_keys[keycode]
                 : base_keymap[keycode];
  }

  if (e.shifted) {
    emit_combined_key(fd, KEY_LEFTSHIFT, e.code);
  } else if (in_ctrl_comb) {
    in_ctrl_comb = 0;
    emit_combined_key(fd, KEY_LEFTCTRL, e.code);
  } else if (e.code == KEY_LEFTCTRL) {
    in_ctrl_comb = 1;
  } else {
    emit_key(fd, e.code, 1);
    emit_key(fd, e.code, 0);
  }
  return e;
}

long long last_press_started[NROWS * NCOLS] = {0};

#define MAX_PRESSED_KEYS 2

int main() {
  int uinput_fd = setup();
  int pressed[NROWS * NCOLS];
  int pressed_count = 0;
  memset(pressed, 0, sizeof(pressed));
  for (;;) {
    usleep(1000000 / 60);
    int current_pressed_keys = 0;
    for (int i = 0; i < NROWS; i++) {
      rpi_gpio_output(rows[i], 0);
      rpi_gpio_set_fn(rows[i], OUTPUT);
      usleep(3);
      uint32_t all = rpi_gpio_input_all();
      rpi_gpio_set_fn(rows[i], INPUT);
      for (int j = 0; j < NCOLS; j++) {
        int keycode = i * NCOLS + j;
        int val = !(all & (1 << cols[j]));
        if (pressed[keycode] != val) {
          pressed[keycode] = val;
          printf("%d, %d %s\n", i, j, val ? "pressed" : "released");
          if (val) {
            current_pressed_keys += 1;
            if (current_pressed_keys >= MAX_PRESSED_KEYS)
              continue;
            last_press_started[keycode] = millis();
          } else {
            current_pressed_keys -= 1;
            int long_press = millis() - last_press_started[keycode] > 300;
            Emitted e = handle_key(uinput_fd, keycode, long_press);
            printf("emitted %s%s\n", e.shifted ? "shifted " : "",
                   keycode_to_string(e.code));
          }
        }
      }
    }
  }
}
