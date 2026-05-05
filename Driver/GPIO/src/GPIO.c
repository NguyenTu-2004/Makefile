#include "GPIO.h"

void GPIO_Init(GPIO_Handle *pGPIOHandle) {
    uint32_t temp = 0; 

    uint8_t config_value = (pGPIOHandle->GPIO_PinConfig.Mode << 2) | pGPIOHandle->GPIO_PinConfig.Speed;

    if (pGPIOHandle->GPIO_PinConfig.PinNumber < 8) {
        uint8_t shift_amount = pGPIOHandle->GPIO_PinConfig.PinNumber * 4;

        temp = pGPIOHandle->GPIOx->CRL;        
        temp &= ~(0xF << shift_amount);         
        temp |= (config_value << shift_amount); 
        pGPIOHandle->GPIOx->CRL = temp;        
    } else {
        uint8_t shift_amount = (pGPIOHandle->GPIO_PinConfig.PinNumber - 8) * 4;

        temp = pGPIOHandle->GPIOx->CRH;        
        temp &= ~(0xF << shift_amount);         
        temp |= (config_value << shift_amount); 
        pGPIOHandle->GPIOx->CRH = temp;        
    }
}

void GPIO_WritePin(GPIO_Reg *GPIOx, uint8_t PinNumber, uint8_t Value) {
    if (Value) {
        GPIOx->BSRR = (1 << PinNumber); 
    } else {
        GPIOx->BRR = (1 << PinNumber);  
    }
}

