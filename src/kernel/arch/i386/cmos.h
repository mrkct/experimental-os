#ifndef CMOS_H
#define CMOS_H

#include <stdint.h>

#define CMOS_PORT_SELECT    0x70
#define CMOS_PORT_READ      0x71

#define CMOS_REG_SECONDS    0x00
#define CMOS_REG_MINUTES    0x02
#define CMOS_REG_HOURS      0x04
#define CMOS_REG_WEEKDAY    0x06
#define CMOS_REG_DAYOFMONTH 0x07
#define CMOS_REG_MONTH      0x08
#define CMOS_REG_YEAR       0x09
#define CMOS_REG_CENTURY    0x32
#define CMOS_REG_STATUSA    0x0A
#define CMOS_REG_STATUSB    0x0B

/*
    Reads the content of the 'index' CMOS register.
*/
uint8_t cmos_read_register(uint8_t index);

/*
    Converts a value from BCD mode to a normal value. A BCD value is a 
    number that is represented in 2 hex digits. For example:
    34 would be represented as 0x34 which is actually 52. This function 
    converts 0x34 in 34 decimal.
    The real time clock registers can return values in BCD mode
*/
uint8_t from_bcd(uint8_t bcd);

#endif