#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <kernel/lib/kassert.h>
#include <kernel/devices/ps2kb/keyboard.h>

#define EVENTQUEUE_SIZE 256

/*
    Represents the pressed status of all the keys. The index of a key is its
    KeyCode value.
*/
static bool keymap_status[256] = {0};

static bool caps_lock_status = false;

/*
    TODO: Change this to a list when we will have a memory allocator.
*/
static struct {
    struct KeyAction events[EVENTQUEUE_SIZE];
    int from, size;
} event_queue;

/*
    Adds an action to the event_queue. 
    Returns:
        1 if it was added successfully
        0 if the queue is full
*/
static int eventqueue_add(struct KeyAction action)
{
    if (event_queue.size == EVENTQUEUE_SIZE) {
        return 0;
    }

    int newindex = (event_queue.from + event_queue.size) % EVENTQUEUE_SIZE;
    event_queue.events[newindex] = action;
    event_queue.size++;

    return 1;
}

/*
    Reads a KeyAction from the event_queue.
    Returns:
        1 if it was read successfully
        0 if the queue was empty
*/
static int eventqueue_read(struct KeyAction *action)
{
    if (event_queue.size == 0) {
        return 0;
    }
    *action = event_queue.events[event_queue.from];
    event_queue.size--;
    event_queue.from = (event_queue.from + 1) % EVENTQUEUE_SIZE;

    return 1;
}

/*
    When this is > 0 every call to kbd_handle_byte will decrement this and 
    ignore the argument byte.
    This is used to handle the special scancodes for print screen & pause
*/
static unsigned int skip_next = 0;

void kbd_handle_byte(unsigned char byte)
{
    /*
        Represents if we are expecting the next byte from the keyboard to be part 
        of the previous one. Some scancodes are composed of 2 bytes, with the first
        being '0xe0'
    */
    static bool escape_code = false;

    if (skip_next > 0) {
        skip_next--;
        return;
    }

    if (!escape_code) {
        if (byte == SCANCODE_ESCAPECODE) {
            escape_code = true;
            return;
        } else if (byte == (SCANCODE_PAUSE & 0xff)) {
            /*
                This is the first byte of the 'pause' key. It is made of 6 
                consecutive bytes. Here we signal to ignore the next 5 bytes 
                that will come. We also already handle the scancode in full.
                The value in kbd_handle_scancode is the 6 bytes
            */
            kbd_handle_scancode(SCANCODE_PAUSE);
            skip_next = 5;
            return;
        }
    }

    if (escape_code) {
        uint8_t print_pressed_2ndbyte = (SCANCODE_PRINT_PRESSED & 0xff00) >> 8;
        uint8_t print_released_2ndbyte = (SCANCODE_PRINT_RELEASED & 0xff00) >> 8;
        if (byte == print_pressed_2ndbyte || byte == print_released_2ndbyte) {
            /*
                These are the first bytes of the 'print released' and 
                'print pressed' keys. They are both made of 4 consecutive bytes. 
                Here we signal to ignore the next 3 bytes that will come. 
                These are the bytes sent (in order) for these keys:
                'print pressed': e0 2a e0 37 
                'print released': e0 b7 e0 aa
            */
            kbd_handle_scancode(
                byte == print_pressed_2ndbyte ? 
                    SCANCODE_PRINT_PRESSED : 
                    SCANCODE_PRINT_RELEASED
            );
            skip_next = 3;
            escape_code = false;
            return;
        }
        escape_code = false;
        kbd_handle_scancode((SCANCODE_ESCAPECODE << 8) || byte);
        return;
    }

    kbd_handle_scancode(byte);
}

void kbd_handle_scancode(Scancode scancode)
{
    KeyCode keycode = kbd_scancode_to_keycode(scancode);
    keymap_status[keycode] = SCANCODE_KEY_PRESSED(scancode);

    struct KeyAction action;
    action.character = kbd_keycode_to_char(keycode);
    action.keycode = keycode;
    action.scancode = scancode;
    action.pressed = keymap_status[keycode];
    // TODO:
    action.modifiers.capslock   = caps_lock_status;
    action.modifiers.shift      = keymap_status[KEYCODE_SHIFT];
    action.modifiers.shiftr     = keymap_status[KEYCODE_SHIFTR];
    action.modifiers.alt        = keymap_status[KEYCODE_ALT];
    // action.modifiers.altgr      = keymap_status[KEYCODE_ALTGR];
    action.modifiers.ctrl       = keymap_status[KEYCODE_CTRL];
    // action.modifiers.ctrlr      = keymap_status[KEYCODE_CTRLR];
    
    if (keycode == KEYCODE_CAPSLOCK && action.pressed) {
        caps_lock_status = !caps_lock_status;
    }

    eventqueue_add(action);
}

/*
    Returns the last KeyAction in queue. Returns :
    - 0 if there is no KeyAction to read
    - 1 if a KeyAction was read and put in the argument
    Once a KeyAction is read it is removed from the queue 
*/
int kbd_get_keyaction(struct KeyAction *action)
{
    return eventqueue_read(action);
}

/*
    Convers a scancode to a keycode, a 1byte generic identifier.
*/
KeyCode kbd_scancode_to_keycode(Scancode scancode)
{
    /*
        Warning: this implementation only works for the scan code set 1 for a 
        US QWERTY layout. To implement other layouts we will probably need to 
        map each key individually.

        See: https://wiki.osdev.org/PS2_Keyboard#Scan_Code_Set_1

        The conversion is implemented as follow:
        - single byte scancodes are returned with the 7th bit set to 0
        - 2 bytes scancodes have their escape code 0'ed and the 7th bit set to 1
        - the pause and print key are remapped to special constants
          KEYCODE_PRINT and KEYCODE_PAUSE
    */
    // The 7th bit is used to represents if a key was pressed.
    // The same key pressed & released are still the same key though
    // We set this bit to 0 so that we can treat the 2 scancodes the same
    scancode = scancode & ~(1 << 7);
    
    if (scancode == SCANCODE_PRINT_PRESSED) {
        return KEYCODE_PRINT;
    } else if (scancode == SCANCODE_PAUSE) {
        return KEYCODE_PAUSE;
    }
    
    /*
        We re-map all the 2 bytes scancodes to where all the 'key released' 
        scancodes started, at 0x81 (10000000 in binary)
    */
    if ( ((scancode & 0xff00) >> 8) == SCANCODE_ESCAPECODE ) {
        return (scancode & 0xff) | (1 << 7);
    }

    return scancode;
}

static char charmap_normal[CHARMAP_SIZE] = {
    0, 0, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', 
    '-', '=', '\b', '\t', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 
    'o', 'p', '[', ']', '\n', 0, 'a', 's', 'd', 'f', 'g', 'h', 
    'j', 'k', 'l', ';', '\'', '`', 0, '\\', 'z', 'x', 'c', 'v', 
    'b', 'n', 'm', ',', '.', '/', 0, '*', 0, ' ', 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
    '7', '8', '9', '-', '4', '5', '6', '+', '1', '2', '3', '0', '.'
};

static char charmap_shift[CHARMAP_SIZE] = {
    0, 0, '!', '@', '#', '$', '%', '^', '&', '*', '(', ')', 
    '_', '+', '\b', '\t', 'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 
    'O', 'P', '{', '}', '\n', 0, 'A', 'S', 'D', 'F', 'G', 'H', 
    'J', 'K', 'L', ':', '"', '`', 0, '|', 'Z', 'X', 'C', 'V', 
    'B', 'N', 'M', '<', '>', '?', 0, '*', 0, ' ', 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
    '7', '8', '9', '-', '4', '5', '6', '+', '1', '2', '3', '0', '.'
};

char kbd_keycode_to_char(KeyCode keycode)
{
    /*
        TODO: Use a different keymap for caps lock. Expected behaviour is that
        pressing the numbers with caps on should still write numbers
    */
    char *charmap = charmap_normal;
    if (keymap_status[KEYCODE_SHIFT] ^ caps_lock_status) {
        charmap = charmap_shift;
    }
    if (keycode < CHARMAP_SIZE)
        return charmap[keycode];
    else
        return 0;
}