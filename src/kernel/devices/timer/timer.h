#ifndef TIMER_H
#define TIMER_R

void timer_init(uint16_t);
uint32_t timer_get_ticks();
void __timer_tick();

#endif