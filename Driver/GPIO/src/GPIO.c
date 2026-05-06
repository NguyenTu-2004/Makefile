#include "gpio.h"

/* ================= CLOCK ================= */

void GPIO_PeriClockControl(GPIO_Reg *GPIOx, uint8_t EnorDi)
{
    if(EnorDi)
    {
        if(GPIOx == GPIOA) GPIOA_CLK_EN();
        else if(GPIOx == GPIOB) GPIOB_CLK_EN();
        else if(GPIOx == GPIOC) GPIOC_CLK_EN();
    }
}

/* ================= INIT ================= */

void GPIO_Init(GPIO_Handle *pGPIOHandle)
{
    GPIO_PeriClockControl(pGPIOHandle->GPIOx, 1);

    uint32_t temp = 0;
    uint8_t pin = pGPIOHandle->GPIO_PinConfig.PinNumber;

    /* ================= NORMAL GPIO ================= */
    if(pGPIOHandle->GPIO_PinConfig.Mode <= GPIO_MODE_OUTPUT_50MHZ)
    {
        if(pGPIOHandle->GPIO_PinConfig.Mode == GPIO_MODE_INPUT)
        {
            temp |= (0 << 0); // MODE

            if(pGPIOHandle->GPIO_PinConfig.IType == GPIO_INPUT_ANALOG)
                temp |= (0 << 2);

            else if(pGPIOHandle->GPIO_PinConfig.IType == GPIO_INPUT_FLOATING)
                temp |= (1 << 2);

            else if(pGPIOHandle->GPIO_PinConfig.IType == GPIO_INPUT_PU_PD)
            {
                temp |= (2 << 2);

                if(pGPIOHandle->GPIO_PinConfig.OType)
                    pGPIOHandle->GPIOx->ODR |= (1 << pin);
                else
                    pGPIOHandle->GPIOx->ODR &= ~(1 << pin);
            }
        }
        else
        {
            temp |= (pGPIOHandle->GPIO_PinConfig.Mode << 0);   // MODE
            temp |= (pGPIOHandle->GPIO_PinConfig.OType << 2);  // CNF
        }

        if(pin < 8)
        {
            pGPIOHandle->GPIOx->CRL &= ~(0xF << (pin * 4));
            pGPIOHandle->GPIOx->CRL |= (temp << (pin * 4));
        }
        else
        {
            uint8_t pos = pin - 8;
            pGPIOHandle->GPIOx->CRH &= ~(0xF << (pos * 4));
            pGPIOHandle->GPIOx->CRH |= (temp << (pos * 4));
        }
    }

    /* ================= INTERRUPT ================= */
    else
    {
        uint8_t pin = pGPIOHandle->GPIO_PinConfig.PinNumber;

        /* config GPIO as input floating */
        temp = 0;
        temp |= (0 << 0);
        temp |= (1 << 2);

        if(pin < 8)
        {
            pGPIOHandle->GPIOx->CRL &= ~(0xF << (pin * 4));
            pGPIOHandle->GPIOx->CRL |= (temp << (pin * 4));
        }
        else
        {
            uint8_t pos = pin - 8;
            pGPIOHandle->GPIOx->CRH &= ~(0xF << (pos * 4));
            pGPIOHandle->GPIOx->CRH |= (temp << (pos * 4));
        }

        /* 1. edge trigger */
        if(pGPIOHandle->GPIO_PinConfig.Mode == GPIO_MODE_IT_FT)
        {
            EXTI->FTSR |= (1 << pin);
            EXTI->RTSR &= ~(1 << pin);
        }
        else if(pGPIOHandle->GPIO_PinConfig.Mode == GPIO_MODE_IT_RT)
        {
            EXTI->RTSR |= (1 << pin);
            EXTI->FTSR &= ~(1 << pin);
        }
        else
        {
            EXTI->RTSR |= (1 << pin);
            EXTI->FTSR |= (1 << pin);
        }

        /* 2. enable IMR */
        EXTI->IMR |= (1 << pin);

        /* 3. AFIO mapping */
        RCC->APB2ENR |= (1 << 0);

        uint8_t temp1 = pin / 4;
        uint8_t temp2 = (pin % 4) * 4;

        AFIO->EXTICR[temp1] &= ~(0xF << temp2);

        uint8_t portcode = 0;
        if(pGPIOHandle->GPIOx == GPIOA) portcode = 0;
        else if(pGPIOHandle->GPIOx == GPIOB) portcode = 1;
        else if(pGPIOHandle->GPIOx == GPIOC) portcode = 2;

        AFIO->EXTICR[temp1] |= (portcode << temp2);
    }
}

/* ================= BASIC ================= */

void GPIO_WritePin(GPIO_Reg *GPIOx, uint8_t PinNumber, uint8_t Value)
{
    if(Value) GPIOx->BSRR = (1 << PinNumber);
    else GPIOx->BRR = (1 << PinNumber);
}

uint8_t GPIO_ReadPin(GPIO_Reg *GPIOx , uint8_t PinNumber)
{
    return (GPIOx->IDR >> PinNumber) & 0x1;
}

void GPIO_TogglePin(GPIO_Reg *GPIOx, uint8_t PinNumber)
{
    GPIOx->ODR ^= (1 << PinNumber);
}

/* ================= IRQ ================= */

void GPIO_IRQHandling(uint8_t PinNumber)
{
    if(EXTI->PR & (1 << PinNumber))
    {
        EXTI->PR |= (1 << PinNumber);
        GPIO_IRQCallback(PinNumber);
    }
}

void GPIO_IRQConfig(uint8_t IRQNumber, uint8_t EnorDi)
{
    if(EnorDi)
    {
        if(IRQNumber <= 31)
            NVIC_ISER0 |= (1 << IRQNumber);
        else
            NVIC_ISER1 |= (1 << (IRQNumber % 32));
    }
}

void GPIO_IRQPriorityConfig(uint8_t IRQNumber, uint32_t IRQPriority)
{
    uint8_t iprx = IRQNumber / 4;
    uint8_t shift = (IRQNumber % 4) * 8 + 4;
    NVIC_IPR[iprx] |= (IRQPriority << shift);
}

/* ================= CALLBACK ================= */

__attribute__((weak)) void GPIO_IRQCallback(uint8_t PinNumber)
{
}