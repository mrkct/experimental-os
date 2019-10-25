#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <lib/input/scancode.h>
#include <kernel/i686/x86.h>

/* 
    See https://wiki.osdev.org/PS2_Keyboard#Scan_Code_Set_1
    Note: not all keys have been mapped. Some missing are:
    - the entire keypad
    - multimedia keys (not all keyboards have these. For example: play, pause, email etc)

    This maps a US keyboard layout. Also only the 'key pressed' scancodes are mapped, as the 
    'key released' are the same of the key pressed except with the 7th bit set
*/
static enum Key keymap[] = {
    0x0, KEY_ESCAPE, KEY_1, KEY_2, KEY_3, KEY_4, KEY_5, KEY_6, KEY_7, KEY_8, 
    KEY_9, KEY_0, KEY_MINUS, KEY_EQUAL, KEY_BACKSPACE, KEY_TAB, KEY_Q, KEY_W, KEY_E, KEY_R, 
    KEY_T, KEY_Y, KEY_U, KEY_I, KEY_O, KEY_P, KEY_BRACKET1, KEY_BRACKET2, KEY_ENTER, 
    KEY_LEFT_CTRL, KEY_A, KEY_S, KEY_D, KEY_F, KEY_G, KEY_H, KEY_J, KEY_K, 
    KEY_L, KEY_SEMICOLON, KEY_QUOTE, KEY_BACKTICK, KEY_LEFT_SHIFT, KEY_BACKSLASH, KEY_Z, KEY_X, KEY_C, 
    KEY_V, KEY_B, KEY_N, KEY_M, KEY_COMMA, KEY_PERIOD, KEY_SLASH, KEY_RIGHT_SHIFT, 0x37, 
    KEY_LEFT_ALT, KEY_SPACE, KEY_CAPSLOCK, KEY_F1, KEY_F2, KEY_F3, KEY_F4, KEY_F5, KEY_F6, 
    KEY_F7, KEY_F8, KEY_F9, KEY_F10, KEY_NUMLOCK, KEY_SCROLLLOCK, 0x47, 0x48, 0x49, 
    0x4a, 0x4b, 0x4c, 0x4d, 0x4e, 0x4f, 0x50, 0x51, 0x52, 
    0x53, 0x54, 0x55, 0x56, KEY_F11, KEY_F12, 0x59, 0x5a, 0x5b, 
    0x5c, 0x5d, 0x5e, 0x5f, 0x60, 0x61, 0x62, 0x63, 0x64, 
    0x65, 0x66, 0x67, 0x68, 0x69, 0x6a, 0x6b, 0x6c, 0x6d, 
    0x6e, 0x6f, 0x70, 0x71, 0x72, 0x73, 0x74, 0x75, 0x76, 
    0x77, 0x78, 0x79, 0x7a, 0x7b, 0x7c, 0x7d, 0x7e, 0x7f, 
    0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 
    0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f, 0x90, 0x91, 
    0x92, 0x93, 0x94, 0x95, 0x96, 0x97, 0x98, 0x99, 0x9a, 
    0x9b, 0x9c, 0x9d, 0x9e, 0x9f, 0xa0, 0xa1, 0xa2, 0xa3, 
    0xa4, 0xa5, 0xa6, 0xa7, 0xa8, 0xa9, 0xaa, 0xab, 0xac, 
    0xad, 0xae, 0xaf, 0xb0, 0xb1, 0xb2, 0xb3, 0xb4, 0xb5, 
    0xb6, 0xb7, 0xb8, 0xb9, 0xba, 0xbb, 0xbc, 0xbd, 0xbe, 
    0xbf, 0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7, 
    0xc8, 0xc9, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0xcf, 0xd0, 
    0xd1, 0xd2, 0xd3, 0xd4, 0xd5, 0xd6, 0xd7, 0xd8, 0xd9, 
    0xda, 0xdb, 0xdc, 0xdd, 0xde, 0xdf, 0xe0, 0xe1, 0xe2, 
    0xe3, 0xe4, 0xe5, 0xe6, 0xe7, 0xe8, 0xe9, 0xea, 0xeb, 
    0xec, 0xed, 0xee, 0xef, 0xf0, 0xf1, 0xf2, 0xf3, 0xf4, 
    0xf5, 0xf6, 0xf7, 0xf8, 0xf9, 0xfa, 0xfb, 0xfc, 0xfd, 
    0xfe, 0xff
};

struct ScancodeQueue scancodeQueue = { 0 };

/*
    Adds the argument scancode to the global scancodes queue. 
    Before adding you should the queue is not full with ScancodeQueue_empty 
    Returns:
        0 on success
        -E_SCANCODEQ_FULL when the queue is full
*/
int ScancodeQueue_add(Scancode scancode)
{
    if (scancodeQueue.size == SCANCODEQ_SIZE) {
        return -E_SCANCODEQ_FULL;
    }
    int newindex = (scancodeQueue.from + scancodeQueue.size) % SCANCODEQ_SIZE;
    scancodeQueue.data[newindex] = scancode;
    scancodeQueue.size++;

    return 0;
}

/*
    Reads one scancode and puts it in the argument. Before calling this check 
    the queue is not empty.
    Returns:
        0 on success
        -E_SCANCODEQ_EMPTY when there is nothing that can be returned
*/
int ScancodeQueue_read(Scancode *out)
{
    if (ScancodeQueue_empty()) {
        return -E_SCANCODEQ_EMPTY;;
    }
    *out = scancodeQueue.data[scancodeQueue.from];
    scancodeQueue.size--;
    scancodeQueue.from = (scancodeQueue.from + 1) % SCANCODEQ_SIZE;

    return 0;
}

/*
    Returns whenever the scancode queue is empty
*/
bool ScancodeQueue_empty()
{
    return scancodeQueue.size == 0;
}

/*
    Returns whenever the scancode queue is full
*/
bool ScancodeQueue_full()
{
    return scancodeQueue.size == SCANCODEQ_SIZE;
}

/*
    Converts a scancode to its corresponding KeyEvent
*/
int Scancode_to_KeyEvent(Scancode scancode, struct KeyEvent *event)
{
    event->scancode = scancode;
    if (scancode == 0xe0 || scancode == 0xf0) {
        event->escape_code = true;
        return 0;
    }
    event->escape_code = false;
    event->pressed = !( (scancode & SCANCODE_KEYRELEASED_MASK) == SCANCODE_KEYRELEASED_MASK);
    event->key = keymap[scancode & ~SCANCODE_KEYRELEASED_MASK];

    return 0;
}