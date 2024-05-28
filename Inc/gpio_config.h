#include <main.h>

#ifndef GPIO_CONFIG_H_
#define GPIO_CONFIG_H_

typedef struct
{
	uint32_t Pin;
	uint32_t Mode;
	uint32_t Type;
	uint32_t Pull;
} GPIO_ConfigTypeDef;

void gpio_config(GPIO_ConfigTypeDef *GPIO_ConfigStruct);
void gpio_write_pin(GPIO_TypeDef *GPIO_Port, int GPIO_Pin, int State);
int gpio_read_pin(GPIO_TypeDef *GPIO_Port, int GPIO_Pin);



#endif /* GPIO_CONFIG_H_ */
