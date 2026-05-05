#include "GPIO.h"

static void delay(volatile uint32_t t) {
    while (t--) {
        __asm__("nop");
    }
}

int main(void) {
    (*(volatile uint32_t*)0x40021018) |= (1 << 4); // Enable clock for GPIOC
    GPIO_Handle UserLed;
    UserLed.GPIOx = GPIOC;
    UserLed.GPIO_PinConfig.PinNumber = 13;
    UserLed.GPIO_PinConfig.Mode = 0x00; // Output mode, max speed
    UserLed.GPIO_PinConfig.Speed = 0x02; // 2 MHz

    GPIO_Init(&UserLed);

    while (1) {
        GPIO_WritePin(GPIOC, 13, 1); // LED ON
        delay(800000);

        GPIO_WritePin(GPIOC, 13, 0);   // LED OFF
        delay(800000);
    }
}
