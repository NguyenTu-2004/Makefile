#include "GPIO.h"

static void delay(volatile uint32_t t) {
    while (t--) {
        __asm__("nop");
    }
}

int main(void) {
    GPIO_Init_PC13();

    while (1) {
        GPIO_Reset_PC13(); // LED ON
        delay(800000);

        GPIO_Set_PC13();   // LED OFF
        delay(800000);
    }
}
