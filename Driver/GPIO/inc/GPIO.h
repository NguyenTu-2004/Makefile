#ifndef GPIO_H
#define GPIO_H

#include "stm32f103_base.h"

#define GPIO_PIN_NO_0    0
#define GPIO_PIN_NO_1    1
#define GPIO_PIN_NO_2    2
#define GPIO_PIN_NO_3    3
#define GPIO_PIN_NO_4    4
#define GPIO_PIN_NO_5    5
#define GPIO_PIN_NO_6    6
#define GPIO_PIN_NO_7    7
#define GPIO_PIN_NO_8    8
#define GPIO_PIN_NO_9    9
#define GPIO_PIN_NO_10   10
#define GPIO_PIN_NO_11   11
#define GPIO_PIN_NO_12   12
#define GPIO_PIN_NO_13   13
#define GPIO_PIN_NO_14   14
#define GPIO_PIN_NO_15   15

#define GPIO_MODE_INPUT                 0
#define GPIO_MODE_OUTPUT_10MHZ          1
#define GPIO_MODE_OUTPUT_2MHZ           2
#define GPIO_MODE_OUTPUT_50MHZ          3

#define GPIO_MODE_INPUT_ANALOG          0
#define GPIO_MODE_INPUT_FLOATING        1
#define GPIO_MODE_INPUT_PU_PD           2

#define GPIO_OP_TYPE_PP                 0
#define GPIO_OP_TYPE_OD                 1
#define GPIO_OP_TYPE_AF_PP              2
#define GPIO_OP_TYPE_AF_OD              3

#define GPIO_MODE_IT_FT                 4
#define GPIO_MODE_IT_RT                 5
#define GPIO_MODE_IT_RFT                6

#define GPIO_IRQ_RISING             0
#define GPIO_IRQ_FALLING            1
#define GPIO_IRQ_RFT                2

typedef struct{
    uint8_t PinNumber;
    uint8_t Mode;
    uint8_t Speed;
    uint8_t OType;
    uint8_t IType;
}GPIO_Config;

typedef struct{
    GPIO_Reg *GPIOx;
    GPIO_Config GPIO_PinConfig;
}GPIO_Handle;

void GPIO_Init(GPIO_Handle *GPIOx);
void GPIO_DeInit(GPIO_Reg *GPIOx);
void GPIO_WritePin(GPIO_Reg *GPIOx, uint8_t PinNumber, uint8_t Value);
void GPIO_PeriClockControl(GPIO_Reg *GPIOx, uint8_t EnorDi);
uint8_t GPIO_ReadPin(GPIO_Reg *GPIOx , uint8_t PinNumber);
void GPIO_TogglePin(GPIO_Reg *GPIOx, uint8_t PinNumber);

void GPIO_IRQCallback(uint8_t PinNumber);
void GPIO_IRQConfig(uint8_t IRQNumber, uint8_t EnorDi);
void GPIO_IRQPriorityConfig(uint8_t IRQNumber, uint32_t IRQPriority);
void GPIO_IRQHandling(uint8_t PinNumber);
#endif