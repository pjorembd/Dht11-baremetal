#include <main.h>
#include <gpio_config.h>

/**
  * @brief  Set the GPIO peripheral with the values provided by the GPIO structure
  * @param  GPIO_ConfigStruct The structure with the values for the GPIO configuration
  * @retval None
  */
void gpio_config(GPIO_ConfigTypeDef *GPIO_ConfigStruct){

	/*
	 I am aware that this is an inflexible method, in case of need to change to another type of mode,
	 I should use something like a for loop.
	 But this code is created to squeeze all the potential without losing time on
	 checking posible conditions, because for this, already exists the stm32 HAL
	 Also, this is only for demostration purpose, by writing this I'm letting you know
	 that I'm aware that this maybe is not suitable for all situations
	 */

	uint32_t pin = GPIO_ConfigStruct->Pin;
	uint32_t mode = GPIO_ConfigStruct->Mode;
	uint32_t type = GPIO_ConfigStruct->Type;
	uint32_t pull = GPIO_ConfigStruct->Pull;

	if( mode == GPIO_MODE_INPUT){
		GPIOC->MODER &= ~(1 << 20);
		GPIOC->MODER &= ~(1 << 21);
	}

	if( mode == GPIO_MODE_OUTPUT){
		GPIOC->MODER |=  (1 << 20);
		GPIOC->MODER &= ~(1 << 21);

		if(type == GPIO_TYPE_OUTPUT_OD){
			GPIOC->OTYPER |= (1<<10);
		}else if(GPIO_TYPE_OUTPUT_PP){
			GPIOC->MODER &= ~(1 << 10);
		}

	}

	switch (pull) {
	case GPIO_PULL_NO_PULL:
		GPIOC->PUPDR &= ~(1 << 20);
		GPIOC->PUPDR &= ~(1 << 21);
		break;
	case GPIO_PULL_PULL_UP:
		GPIOC->PUPDR &= ~(1 << 20);
		GPIOC->PUPDR |= (1 << 21);
		break;
	case GPIO_PULL_PULL_DOWN:
		GPIOC->PUPDR |= (1 << 20);
		GPIOC->PUPDR &= ~(1 << 21);
		break;
	case GPIO_PULL_PULL_RESERVED:
		GPIOC->PUPDR |= (1 << 20);
		GPIOC->PUPDR |= (1 << 21);
		break;
	default:
		break;
	}
}

/**
  * @brief  Set the GPIO pin state high or low depending on the parameter
  * @param  GPIO_Port The port of the GPIO (A..C and H)
  * @param  GPIO_Pin The pin of the GPIO (0.. 15)
  * @param  state the state of the pin, maybe GPIO_PIN_HIGH_STATE or GPIO_PIN_LOW_STATE
  * @retval None
  */
void gpio_write_pin(GPIO_TypeDef *GPIO_Port, int GPIO_Pin, int state){

	if (state) {
		GPIO_Port->ODR |= (1 << GPIO_Pin);
	} else {
		GPIO_Port->ODR &= ~(1 << GPIO_Pin);
	}

}

int gpio_read_pin(GPIO_TypeDef *GPIO_Port, int GPIO_Pin){

	uint32_t gpio_pin_value = (GPIOC->IDR >> 10) & 0x1;

			if(gpio_pin_value){
				return 1;
			}else{
				return 0;
			}
}
