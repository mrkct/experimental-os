#ifndef TIME_H
#define TIME_H

struct DateTime {
    int hours, minutes, seconds;
    int year, month, day;
};

/*
    Reads the current date and time (GMT +0) into the argument structure. 
    The date and time is based on the computer's CMOS so it might not be 
    accurate if the battery is dead
    Returns 0 on success, -1 on error
*/
int get_datetime(struct DateTime *datetime);

#endif