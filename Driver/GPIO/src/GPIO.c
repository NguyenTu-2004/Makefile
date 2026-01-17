#include "GPIO.h"

void GPIO_Init_PC13(void) {
    /* Bật clock cho Port C (bit 4 = IOPCEN) */
    RCC_APB2ENR |= (1 << 4);

    /* Cấu hình PC13 output push-pull, tốc độ 2MHz
       PC13 nằm trong CRH (bits [23:20]) */
    GPIOC_CRH &= ~(0xF << 20);
    GPIOC_CRH |=  (0x2 << 20); // MODE13 = 10 (Output 2MHz), CNF13 = 00 (Push-pull)
}

void GPIO_Set_PC13(void) {
    GPIOC_BSRR = (1 << 13); // PC13 = 1 (LED OFF)
}

void GPIO_Reset_PC13(void) {
    GPIOC_BRR = (1 << 13); // PC13 = 0 (LED ON)
}
