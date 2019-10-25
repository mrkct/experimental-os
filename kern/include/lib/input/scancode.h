#ifndef SCANCODE_H
#define SCANCODE_H

#define SCANCODEQ_SIZE 512

#define E_SCANCODEQ_FULL    1
#define E_SCANCODEQ_EMPTY   2

// If the 7th bit of a scancode is = 1 the key was released
#define SCANCODE_KEYRELEASED_MASK 128

typedef unsigned char Scancode;

struct ScancodeQueue {
    Scancode data[SCANCODEQ_SIZE];
    int from;
    int size;
};

int ScancodeQueue_add(Scancode);
int ScancodeQueue_read(Scancode*);
bool ScancodeQueue_empty();
bool ScancodeQueue_full();

enum Key {
    KEY_UNIMPLEMENTED,
    KEY_F0,
    KEY_F1,
    KEY_F2,
    KEY_F3,
    KEY_F4,
    KEY_F5,
    KEY_F6,
    KEY_F7,
    KEY_F8,
    KEY_F9,
    KEY_F10,
    KEY_F11,
    KEY_F12,
    KEY_LEFT_CTRL,
    KEY_RIGHT_CTRL,
    KEY_LEFT_SHIFT,
    KEY_RIGHT_SHIFT,
    KEY_ESCAPE,
    KEY_CAPSLOCK,
    KEY_NUMLOCK,
    KEY_SCROLLLOCK,
    KEY_TAB = '\t',
    KEY_LEFT_ALT,
    KEY_RIGHT_ALT,
    KEY_BACKSPACE = '\b',
    KEY_ENTER = '\n',
    KEY_SPACE = ' ',
    KEY_MINUS = '-',
    KEY_EQUAL = '=',
    KEY_BRACKET1 = '[',
    KEY_BRACKET2 = ']',
    KEY_SEMICOLON = ';',
    KEY_QUOTE = '\'',
    KEY_BACKTICK = '`',
    KEY_COMMA = ',',
    KEY_SLASH = '/',
    KEY_BACKSLASH = '\\',
    KEY_PERIOD = '.',
    KEY_A = 'a',
    KEY_B = 'b',
    KEY_C = 'c',
    KEY_D = 'd',
    KEY_E = 'e',
    KEY_F = 'f',
    KEY_G = 'g',
    KEY_H = 'h',
    KEY_I = 'i',
    KEY_J = 'j',
    KEY_K = 'k',
    KEY_L = 'l',
    KEY_M = 'm',
    KEY_N = 'n',
    KEY_O = 'o',
    KEY_P = 'p',
    KEY_Q = 'q',
    KEY_R = 'r',
    KEY_S = 's',
    KEY_T = 't',
    KEY_U = 'u',
    KEY_V = 'v',
    KEY_W = 'w',
    KEY_X = 'x',
    KEY_Y = 'y',
    KEY_Z = 'z',
    KEY_0 = '0',
    KEY_1 = '1',
    KEY_2 = '2',
    KEY_3 = '3',
    KEY_4 = '4',
    KEY_5 = '5',
    KEY_6 = '6',
    KEY_7 = '7',
    KEY_8 = '8',
    KEY_9 = '9'
};

/*
    Contains a simpler representation of a 1 byte scancode.
*/
struct KeyEvent {
    Scancode scancode;      // The original scancode byte
    enum Key key;           // Which key the scancode refers to
    bool pressed;           // Was it a key pressed event? or released?
    bool escape_code;       // Was it a special scancode that requires to read more?
};

int Scancode_to_KeyEvent(Scancode, struct KeyEvent*);

#endif