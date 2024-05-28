/**
 ******************************************************************************
 * @file    stm32f410rb.h
 * @author  PabCab1409
 * @brief   CMSIS STM32F410RB Device Peripheral Access Layer Header File.
 *
 *          This file contains:
 *           - Data structures and the address mapping for necesary peripherals
 *           - Peripherals registers declarations and bits definition
 *           - Macros to access peripheral's registers hardware
 *
 ******************************************************************************
 */
#ifndef STM32F410RB_H_
#define STM32F410RB_H_

#include "main.h"
#include <stdint.h>

/////////////////////// TIMER SPECS DEFINITION ///////////////////////
#define SystemCoreClock											16000000
/////////////////////// PERIPHERAL ADDRESSES DEFINITION ///////////////////////

#define PERIPH_BASE												0x40000000UL
#define CORTEX_PERIPH_BASE								0xE000E010U


#define AHB1_PERIPH_OFFSET 								0x00020000UL

#define AHB1_PERIPH_BASE									(PERIPH_BASE + AHB1_PERIPH_OFFSET)

#define RCC_OFFSET												0x3800UL
#define RCC_PERIPH_BASE										(AHB1_PERIPH_BASE + RCC_OFFSET)

#define GPIOC_OFFSET											0x0800UL
#define GPIOC_BASE													(AHB1_PERIPH_BASE + GPIOC_OFFSET)

#define SYSTICK_TIMER_BASE								(CORTEX_PERIPH_BASE)

#define	GPIOC																((GPIO_TypeDef * ) GPIOC_BASE)
#define RCC																((RCC_TypeDef  * ) RCC_PERIPH_BASE)
#define SysTick															((SysTick_Typdef  *) SYSTICK_TIMER_BASE)

/////////////////////// GPIO PIN DEFINITIONS ///////////////////////
#define  GPIO_PIN_10												1

/////////////////////// MISCELANEOUS DEFINITIONS ///////////////////////
#define GPIO_PIN_HIGH_STATE								1
#define GPIO_PIN_LOW_STATE								0

/////////////////////// PERIPHERAL CONFIGURATION KEYWORDS ///////////////////////
#define  GPIO_MODE_INPUT									1
#define  GPIO_MODE_OUTPUT								2
#define  GPIO_TYPE_OUTPUT_PP 							3
#define  GPIO_TYPE_OUTPUT_OD							4
#define  GPIO_PULL_NO_PULL									5
#define  GPIO_PULL_PULL_UP									6
#define  GPIO_PULL_PULL_DOWN							7
#define  GPIO_PULL_PULL_RESERVED					8

/////////////////////// PERIPHERAL STRUCTURES DEFINITION ///////////////////////
typedef struct
{
	uint32_t CR;
	uint32_t PLLCFGR;
	uint32_t CFGR;
	uint32_t CIR;
	uint32_t AHB1RSTR;
	uint32_t RESERVED0[3];
	uint32_t APB1RSTR;
	uint32_t APB2RSTR;
	uint32_t RESERVED1[2];
	uint32_t AHB1ENR;
	uint32_t RESERVED2[3];
	uint32_t APB1ENR;
	uint32_t APB2ENR;
	uint32_t RESERVED3[2];
	uint32_t AHB1LPENR;
	uint32_t RESERVED4[3];
	uint32_t APB1LPENR;
	uint32_t APB2LPENR;
	uint32_t RESERVED5[2];
	uint32_t BDCR;
	uint32_t CSR;
	uint32_t RESERVED6[2];
	uint32_t SSCGR;
	uint32_t RESERVED7[2];
	uint32_t DCKCFGR;
	uint32_t CKGATENR;
	uint32_t DCKCFGR2;
} RCC_TypeDef;

typedef struct
{
	uint32_t MODER;
	uint32_t OTYPER;
	uint32_t OSPEEDR;
	uint32_t PUPDR;
	uint32_t IDR;
	uint32_t ODR;
	uint32_t BSRR;
	uint32_t LCKR;
	uint32_t AFR[2];
} GPIO_TypeDef;

typedef struct{
	uint32_t STK_CTRL;
	uint32_t STK_LOAD;
	uint32_t STK_VAL;
	uint32_t STK_CALIB;
} SysTick_Typdef;


#endif /* STM32F410RB_H_ */
