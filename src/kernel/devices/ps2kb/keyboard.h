#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>

#define SCANCODE_KEY_PRESSED(s) ((s & (1 << 7)) == 0)

#define SCANCODE_PRINT_PRESSED      0x37e02ae0
#define SCANCODE_PRINT_RELEASED     0xaae0b7e0
#define SCANCODE_ESCAPECODE         0xe0
#define SCANCODE_PAUSE              0xc59de1451de1

#define CHARMAP_SIZE  0x55

// TODO: #define all the keycodes

#define KEYCODE_PRINT       0xfe
#define KEYCODE_PAUSE       0xff

#define KEYCODE_SHIFT       0x2a
#define KEYCODE_CAPSLOCK    0x3a
#define KEYCODE_SHIFTR      0x36
#define KEYCODE_CTRL        0x1d
#define KEYCODE_ALT         0x38

typedef uint64_t Scancode;
typedef uint8_t KeyCode;

struct KeyAction {
    char character;
    KeyCode keycode;
    Scancode scancode;
    bool pressed;
    struct {
        unsigned int shift : 1;
        unsigned int shiftr : 1;
        unsigned int capslock : 1;
        unsigned int alt : 1;
        unsigned int altgr : 1;
        unsigned int ctrl : 1;
        unsigned int ctrlr : 1;
    } modifiers;
};

void kbd_handle_byte(unsigned char);
void kbd_handle_scancode(Scancode code);
KeyCode kbd_scancode_to_keycode(Scancode code);
int kbd_get_keyaction(struct KeyAction*);
bool kbd_key_down(KeyCode);
char kbd_keycode_to_char(KeyCode);

#endif 