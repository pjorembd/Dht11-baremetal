//#include <main.h>
//#include <stdint.h>
//
//
//
//int main(void) {
//
//	enable_AHB1_bus();
//	GPIO_ConfigTypeDef GPIO_ConfigStruct = { 0 };
//	GPIO_ConfigStruct.Mode = GPIO_MODE_OUTPUT;
//	GPIO_ConfigStruct.Type = GPIO_TYPE_OUTPUT_OD;
//	gpio_config(&GPIO_ConfigStruct);
//	uint32_t countflag;
//
//	while (1) {
//		gpio_write_pin(GPIOC, 10, GPIO_PIN_HIGH_STATE);
//		delayMs(1000);//1 segundo 1000ms /
//		gpio_write_pin(GPIOC, 10, GPIO_PIN_LOW_STATE);
//		//DHT11 RESET PULSE
////		gpio_write_pin(GPIOC, 10, GPIO_PIN_HIGH_STATE);
////		gpio_write_pin(GPIOC, 10, GPIO_PIN_LOW_STATE);
//
////		//input mode for pull up
////		GPIO_ConfigStruct.Mode = GPIO_MODE_INPUT;
////		GPIO_ConfigStruct.Pull = GPIO_PULL_PULL_UP;
////		gpio_config(&GPIO_ConfigStruct);
//	}
//
//}
////////////////////////////////////////////////////// anterior ////////////////////////
#include <main.h>
#include <stdint.h>

#define is_dht_signal_low 			!gpio_read_pin(GPIOC, 10)
#define is_dht_signal_high			gpio_read_pin(GPIOC, 10)

int dht_high_signal_sent, dht_low_signal_sent;
GPIO_ConfigTypeDef GPIO_ConfigStruct = { 0 };
uint8_t i,j;
uint8_t Rh_byte1, Rh_byte2, Temp_byte1, Temp_byte2;
float temp1, temp2, hum1, hum2;
uint16_t SUM;

int main(void) {

	enable_AHB1_bus();
	GPIO_ConfigStruct.Mode = GPIO_MODE_OUTPUT;
	GPIO_ConfigStruct.Type = GPIO_TYPE_OUTPUT_OD;
	gpio_config(&GPIO_ConfigStruct);

	while (1) {
//		delayMs(1000);
//		init_dht11();
//		Rh_byte1 = read_dht11();
//		hum1 = Rh_byte1;
//		Rh_byte2 = read_dht11();
//		hum2 = Rh_byte2;
//		Temp_byte1 = read_dht11();
//		temp1 = Temp_byte1;
//		Temp_byte2 = read_dht11();
//		temp2 = Temp_byte2;
//		SUM = read_dht11();
//
//		if (SUM == (Rh_byte1 + Rh_byte2 + Temp_byte1 + Temp_byte2)) {
//			//Correct
//		}
		gpio_write_pin(GPIOC, 10,1);
		delayMs(4000);
		gpio_write_pin(GPIOC, 10,0);
	}
}

void init_dht11() {
	/*
	 * Gpio output mode config
	 */
	GPIO_ConfigStruct.Mode = GPIO_MODE_OUTPUT;
	GPIO_ConfigStruct.Type = GPIO_TYPE_OUTPUT_OD;
	gpio_config(&GPIO_ConfigStruct);

	/*
	 * In order to activate the dth11 sensor, you need to follow the start signal instructions (more info in the datasheet).
	 * This is achived by  sending a high voltage signal (first I set it to low so dht11 could notice the difference) for 18ms.
	 * Then, I let the pull up resistor goes up by changing the gpio input and pull up mode.
	 */
	gpio_write_pin(GPIOC, 10, GPIO_PIN_HIGH_STATE);
	gpio_write_pin(GPIOC, 10, GPIO_PIN_LOW_STATE);
	delayMs(18);
	/*
	 * Then, I let the pull up resistor goes up by changing the gpio input and pull up mode.
	 */
	GPIO_ConfigStruct.Mode = GPIO_MODE_INPUT;
	GPIO_ConfigStruct.Pull = GPIO_PULL_PULL_UP;
	gpio_config(&GPIO_ConfigStruct);

	/*
	 * Check dht11's response. Dht will send out response signal by keeping low for 80us, and then will pull up voltage
	 * staying high (pull up) for 80us. After this, it will start sending humidity and temperature data.
	 * See datasheet for more information.
	 */
//	toDo maybe is not necesary to check if it is low
	while (is_dht_signal_low){dht_low_signal_sent = 1;}
	while (is_dht_signal_high) {dht_high_signal_sent = 1;}//toDo add timeouts
}

int dht11_is_ready(void) {

	if (dht_high_signal_sent & dht_low_signal_sent) {
		return 1;
	}

	return 0;

}

uint8_t read_dht11(void) {

	if (!dht11_is_ready()) {
		init_dht11();
	}

	/*
	 * Response reading process
	 * It is all detailed in dth11 datasheet
	 */
	for (int j = 0; j < 8; ++j) {

		/*
		 * start to transmit 1-bit data (50us)
		 */
		while (is_dht_signal_low);

		/*
		 * 26-28us voltage-lentgh bit means 0 (I use 30 to round)
		 * 70us voltage-lentgh bit means 1, so if it is low after 30us, it means that bit is 1
		 */
		delayUs(30);
		if (is_dht_signal_low) {
			i &= ~(1 << (7 - j));	//bit is 0
		} else {
			i |= (1 << (7 - j));		//bit is 1
		}
		while (is_dht_signal_high);

	}

	return i;

}


