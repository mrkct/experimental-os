#ifndef SCANCODE_H
#define SCANCODE_H

#define SCANCODEQ_SIZE 512

#define E_SCANCODEQ_FULL    1
#define E_SCANCODEQ_EMPTY   2

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

#endif