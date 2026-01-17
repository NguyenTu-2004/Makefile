#ifndef GPIO_H
#define GPIO_H

#include <stdint.h>

/* Base address RCC + GPIOC (theo Reference Manual STM32F103x8) */
#define RCC_APB2ENR   (*((volatile uint32_t*)0x40021018))
#define GPIOC_CRH     (*((volatile uint32_t*)0x40011004))
#define GPIOC_BSRR    (*((volatile uint32_t*)0x40011010))
#define GPIOC_BRR     (*((volatile uint32_t*)0x40011014))

/* Hàm khởi tạo GPIO */
void GPIO_Init_PC13(void);

/* Hàm điều khiển LED */
void GPIO_Set_PC13(void);   // Output = 1 (LED tắt)
void GPIO_Reset_PC13(void); // Output = 0 (LED bật)

#endif