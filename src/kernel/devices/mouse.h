#ifndef MOUSE_H
#define MOUSE_H

#include <stdbool.h>

#define MOUSE_WAIT_TIMEOUT  40

#define MOUSE_STATUS_RREADY     0x1     // read ready
#define MOUSE_STATUS_WREADY     0x2     // write ready

#define MOUSE_FLAGS_YOVERFLOW       0x80
#define MOUSE_FLAGS_XOVERFLOW       0x40
#define MOUSE_FLAGS_YSIGN           0x20
#define MOUSE_FLAGS_XSIGN           0x10
#define MOUSE_FLAGS_ALWAYS1         0x8
#define MOUSE_FLAGS_MIDDLEBTN       0x4
#define MOUSE_FLAGS_RIGHTBTN        0x2
#define MOUSE_FLAGS_LEFTBTN         0x1

struct MouseStatus {
    bool connected;
    int x, y;
    bool left, middle, right;
};

int mouse_init(void);

void __mouse_irq(void);

struct MouseStatus mouse_status(void);

#endif