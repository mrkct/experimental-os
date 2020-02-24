#ifndef TIMER_H
#define TIMER_R

void timer_init(uint16_t);

/*
    Returns the divisor used when initialising the timer
*/
uint16_t timer_get_divisor(void);

uint32_t timer_get_ticks();
void __timer_tick();

#endif