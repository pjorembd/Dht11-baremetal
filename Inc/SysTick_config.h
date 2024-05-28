#include <main.h>

#ifndef SYSTICK_CONFIG_H_
#define SYSTICK_CONFIG_H_

void SysTick_init(int ms);
void delayMs(int ms);
void delayUs(int ms);
uint32_t get_systick_cntflg();

#endif /* SYSTICK_CONFIG_H_ */
