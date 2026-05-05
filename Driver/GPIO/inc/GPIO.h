#ifndef GPIO_H
#define GPIO_H

#include <stdint.h>

typedef struct 
{
   volatile uint32_t CRL;
   volatile uint32_t CRH;
   volatile uint32_t IDR;
   volatile uint32_t ODR;
   volatile uint32_t BSRR;
   volatile uint32_t BRR;
   volatile uint32_t LCKR;
}GPIO_Reg;

typedef struct{
    uint8_t PinNumber;
    uint8_t Mode;
    uint8_t Speed;
}GPIO_Config;

typedef struct{
    GPIO_Reg *GPIOx;
    GPIO_Config GPIO_PinConfig;
}GPIO_Handle;

#define GPIOA ((GPIO_Reg *)0x40010800)
#define GPIOB ((GPIO_Reg *)0x40010C00)
#define GPIOC ((GPIO_Reg *)0x40011000)

void GPIO_Init(GPIO_Handle *GPIOx);
void GPIO_WritePin(GPIO_Reg *GPIOx, uint8_t PinNumber, uint8_t Value);

#endif