#ifndef SERIAL_H
#define SERIAL_H

#define SERIAL_TIMEOUT 20

/*
    Initializes the serial COM1 port. This depends on the timer being setup 
    so it should only be called after you already have configured the PIT
*/
void serial_init(void);

/*
    Writes the string to the serial console.
    Returns 0 on success, -1 if a timeout occurs while waiting for the 
    serial device to be ready
*/
int serial_write(const char *data);

// int serial_read(char *buffer, size_t size);

enum {
    SERIAL_PORT_BASE_COM1 = 0x3f8, 

    SERIAL_PORT_COM1_DATA = SERIAL_PORT_BASE_COM1, 
    SERIAL_PORT_COM1_INTENABLE = SERIAL_PORT_BASE_COM1 + 1, 
    SERIAL_PORT_COM1_LOWBAUD = SERIAL_PORT_BASE_COM1, 
    SERIAL_PORT_COM1_HIGHBAUD = SERIAL_PORT_BASE_COM1 + 1,
    SERIAL_PORT_COM1_INT_ID = SERIAL_PORT_BASE_COM1 + 2, 
    SERIAL_PORT_COM1_FIFO = SERIAL_PORT_BASE_COM1 + 2, 
    SERIAL_PORT_COM1_LINECONTROL = SERIAL_PORT_BASE_COM1 + 3, 
    SERIAL_PORT_COM1_MODEMCONTROL = SERIAL_PORT_BASE_COM1 + 4, 
    SERIAL_PORT_COM1_LINESTATUS = SERIAL_PORT_BASE_COM1 + 5, 
    SERIAL_PORT_COM1_MODEMSTATUS = SERIAL_PORT_BASE_COM1 + 6, 
    SERIAL_PORT_COM1_SCRATCH = SERIAL_PORT_BASE_COM1 + 7
};

#endif