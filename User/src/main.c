#include "GPIO.h"
#include "stm32f103_base.h"

static void delay(volatile uint32_t t) {
    while (t--) {
        __asm__("nop");
    }
}

int main(void) {
    GPIO_PeriClockControl(GPIOC, ENABLE);
    GPIO_Handle UserLed;
    UserLed.GPIOx = GPIOC;
    UserLed.GPIO_PinConfig.PinNumber = 13;
    UserLed.GPIO_PinConfig.Mode = 0x00; // Output mode, max speed
    UserLed.GPIO_PinConfig.Speed = 0x02; // 2 MHz

    GPIO_Init(&UserLed);

    while (1) {
        GPIO_WritePin(GPIOC, GPIO_PIN_NO_13, SET); 
        delay(800000);

        GPIO_WritePin(GPIOC, GPIO_PIN_NO_13, RESET);
        delay(800000);
    }
}
