#include <SysTick_config.h>



#define STK_CTRL_COUNTFLAG_Pos										16
#define STK_CTRL_CLKSOURCE_AHB									(1U << 2)
#define STK_CTRL_TICKINT_DISBLE_INTRRPT						(1U << 1)
#define STK_CTRL_ENABLE														(1U << 0)



void SysTick_init(int reload_value) {

//	uint32_t reload_value = (SystemCoreClock / 1000) * ms ;
	SysTick->STK_LOAD = reload_value;

	//write any value to reset the counter and the countflag (check stk_val (4.5.3) on arm cortex m4 generic user guide)
	SysTick->STK_VAL |= (1 << 0);

	//select clock source
	SysTick->STK_CTRL |= STK_CTRL_CLKSOURCE_AHB; //  processor clock ahb

	//configure to not assert the sytick interruption
	SysTick->STK_CTRL &= ~STK_CTRL_TICKINT_DISBLE_INTRRPT;

	//enable the counter
	SysTick->STK_CTRL |= STK_CTRL_ENABLE;

}

void calculate_autorreload_value(int ms){

	uint32_t reload_value = (SystemCoreClock / 1000) * ms ;
	uint32_t max_value_systick_timer = 0xFFFFFF;
	int i = 0;
	/*
	 * El delay requiere un reload value que cabe el registro
	 */
	if (reload_value < max_value_systick_timer) {
		SysTick_init(reload_value);
		while (get_systick_cntflg() == 0); //when countflag is 0 means that reload value has been reached (4.5.1, bit 1-> TICKTIN from arm cortex m4 generic user guide)
		return;
	}

	/*
	 * El reload value necesario para obtener un delay de 2 segundos es 32 000 000.
	 * 32 000 000 / 16 777 215 = 1.91
	 * 	Quiere decir que tengo que llenar entero 1 vez el reload value, es decir, con 16 777 215, dejar que se descargue, y despues tengo que
	 * 	rellenar el reload value con el 0.91 * 16 777 215 = 15 222 785.
	 * 	De esta forma, obtengo el delay de 2 segundos, que seria contar hasta 32 000 000 en el reload value,
	 * 	ya que el maximo que puede contar sin ser truncado es hasta 16 777 215.
	 * 	Comprobacion -> 16777215 + 15222785 = 32000000
	 */

	//obtengo repeticion y sobrante
	double repeat_times = reload_value / max_value_systick_timer; //1.91
	int int_part_repeat_times = (int) repeat_times; // 1
	int decimal_part_repeat_times = repeat_times - int_part_repeat_times; // 0.91

	//relleno el reload value entero y repito las veces necesarias
	for (i = 0; i < int_part_repeat_times; i++) {
		SysTick_init(max_value_systick_timer);
		while (get_systick_cntflg() == 0);
	}

	//relleno el reload value con el sobrante que faltaba
	SysTick->STK_LOAD = decimal_part_repeat_times * max_value_systick_timer;
	while (get_systick_cntflg() == 0);

}

void delayMs(int ms) {

	calculate_autorreload_value(ms);

}

void delayUs(int us) {
	double reload_value_us = (SystemCoreClock / 1000.0) * (us/1000.0); //1ms = 1000us, simple math operation so I can get reload value using the same SysTick_init fucntion
	SysTick_init(reload_value_us);
	while (get_systick_cntflg() == 0);

}

uint32_t get_systick_cntflg() {
	return (SysTick->STK_CTRL >> STK_CTRL_COUNTFLAG_Pos) & 0x01;
}

