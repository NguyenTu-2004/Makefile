#ifndef _STM32F104_H_
#define _STM32F104_H_

#include <stdint.h>

/* ============ Base Addresses =============== */
#define SRAM_BASE            0x20000000UL
#define FLASH_BASE           0x08000000UL
#define ROM_BASE             0x1FFF0000UL

#define PERIPH_BASE          0x40000000UL 
#define APB1PERIPH_BASE      PERIPH_BASE                    //0x40000000
#define APB2PERIPH_BASE      (PERIPH_BASE + 0x00010000UL)   //0x4001 0000
#define AHBPERIPH_BASE       (PERIPH_BASE + 0x00018000UL)	//0x4001 8000
#define NVIC_BASE            0xE000E100UL

/* APB2 Peripherals */
#define GPIOA_BASE           (APB2PERIPH_BASE + 0x0800UL)   //0x4001 0800
#define GPIOB_BASE           (APB2PERIPH_BASE + 0x0C00UL)   //0x4001 0C00
#define GPIOC_BASE           (APB2PERIPH_BASE + 0x1000UL)   //0x4001 1000
#define AFIO_BASE            (APB2PERIPH_BASE + 0x0000UL)   //0x4001 0000
#define EXTI_BASE            (APB2PERIPH_BASE + 0x0400UL)   //0x4001 0400
#define ADC1_BASE            (APB2PERIPH_BASE + 0x2400UL)   //0x4001 2400
#define ADC2_BASE            (APB2PERIPH_BASE + 0x2800UL)   //0x4001 2800
#define USART1_BASE          (APB2PERIPH_BASE + 0x3800UL)   //0x4001 3800
#define SPI1_BASE            (APB2PERIPH_BASE + 0x3000UL)   //0x4001 3000
#define TIM1_BASE            (APB2PERIPH_BASE + 0x2C00UL)   //0x4001 2C00


/* APB1 Peripherals */
#define USART2_BASE           (APB1PERIPH_BASE + 0x4400UL)   //0x4001 4400
#define USART3_BASE           (APB1PERIPH_BASE + 0x4800UL)   //0x4001 4800
#define SPI2_BASE             (APB1PERIPH_BASE + 0x3800UL)   //0x4001 3800
#define SPI3_BASE             (APB1PERIPH_BASE + 0x3C00UL)   //0x4001 3C00
#define I2C1_BASE             (APB1PERIPH_BASE + 0x5400UL)   //0x4001 5400
#define I2C2_BASE             (APB1PERIPH_BASE + 0x5800UL)   //0x4001 5800
#define TIM2_BASE             (APB1PERIPH_BASE + 0x0000UL)   //0x4001 0000
#define TIM3_BASE             (APB1PERIPH_BASE + 0x0400UL)   //0x4001 0400
#define TIM4_BASE             (APB1PERIPH_BASE + 0x0800UL)   //0x4001 0800
/* AHB Peripherals */
#define RCC_BASE             (AHBPERIPH_BASE + 0x3000UL)  //0x4002 1000

/* ============ Clock Enable Marcos =============== */

/* GPIO Clock Enable Macros */
#define GPIOA_CLK_EN()       (RCC->APB2ENR |= (1 << 2))
#define GPIOB_CLK_EN()       (RCC->APB2ENR |= (1 << 3))
#define GPIOC_CLK_EN()       (RCC->APB2ENR |= (1 << 4))

/* ADC Clock Enable Macros */
#define ADC1_CLK_EN()       (RCC->APB2ENR |= (1 << 9))
#define ADC2_CLK_EN()       (RCC->APB2ENR |= (1 << 10))

/* UART Clock Enable Macros */
#define USART1_CLK_EN()     (RCC->APB2ENR |= (1 << 14))
#define USART2_CLK_EN()     (RCC->APB1ENR |= (1 << 17))
#define USART3_CLK_EN()     (RCC->APB1ENR |= (1 << 18))

/* SPI Clock Enable Macros */
#define SPI1_CLK_EN()       (RCC->APB2ENR |= (1 << 12))
#define SPI2_CLK_EN()       (RCC->APB1ENR |= (1 << 14))
#define SPI3_CLK_EN()       (RCC->APB1ENR |= (1 << 15))

/* I2C Clock Enable Macros */
#define I2C1_CLK_EN()       (RCC->APB1ENR |= (1 << 21))
#define I2C2_CLK_EN()       (RCC->APB1ENR |= (1 << 22))

/*Timer Clock Enable Macros */
#define TIM1_CLK_EN()       (RCC->APB2ENR |= (1 << 0))
#define TIM2_CLK_EN()       (RCC->APB1ENR |= (1 << 0))
#define TIM3_CLK_EN()       (RCC->APB1ENR |= (1 << 1))
#define TIM4_CLK_EN()       (RCC->APB1ENR |= (1 << 2))

/* ============ Clock Disable Marcos =============== */

/* GPIO Clock Disable Macros */
#define GPIOA_CLK_DIS()      (RCC->APB2ENR &= ~(1 << 2))
#define GPIOB_CLK_DIS()      (RCC->APB2ENR &= ~(1 << 3))
#define GPIOC_CLK_DIS()      (RCC->APB2ENR &= ~(1 << 4))

/* ADC Clock Disable Macros */
#define ADC1_CLK_DIS()       (RCC->APB2ENR &= ~(1 << 9))
#define ADC2_CLK_DIS()       (RCC->APB2ENR &= ~(1 << 10))   

/* UART Clock Disable Macros */
#define USART1_CLK_DIS()     (RCC->APB2ENR &= ~(1 << 14))
#define USART2_CLK_DIS()     (RCC->APB1ENR &= ~(1 << 17))
#define USART3_CLK_DIS()     (RCC->APB1ENR &= ~(1 << 18))

/* SPI Clock Disable Macros */
#define SPI1_CLK_DIS()       (RCC->APB2ENR &= ~(1 << 12))
#define SPI2_CLK_DIS()       (RCC->APB1ENR &= ~(1 << 14))
#define SPI3_CLK_DIS()       (RCC->APB1ENR &= ~(1 << 15))

/* I2C Clock Disable Macros */
#define I2C1_CLK_DIS()       (RCC->APB1ENR &= ~(1 << 21))
#define I2C2_CLK_DIS()       (RCC->APB1ENR &= ~(1 << 22))

/*Timer Clock Disable Macros */
#define TIM1_CLK_DIS()       (RCC->APB2ENR &= ~(1 << 0))
#define TIM2_CLK_DIS()       (RCC->APB1ENR &= ~(1 << 0))
#define TIM3_CLK_DIS()       (RCC->APB1ENR &= ~(1 << 1))
#define TIM4_CLK_DIS()       (RCC->APB1ENR &= ~(1 << 2))

/* ============ Register Definitions =============== */

/* NVIC Registers */
#define NVIC_ISER0   (*(volatile uint32_t*)0xE000E100)
#define NVIC_ISER1   (*(volatile uint32_t*)0xE000E104)

#define NVIC_ICER0   (*(volatile uint32_t*)0xE000E180)
#define NVIC_ICER1   (*(volatile uint32_t*)0xE000E184)

#define NVIC_IPR     ((volatile uint32_t*)0xE000E400)
/* GPIO Registers  */
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

#define GPIOA ((GPIO_Reg *)GPIOA_BASE)
#define GPIOB ((GPIO_Reg *)GPIOB_BASE)
#define GPIOC ((GPIO_Reg *)GPIOC_BASE)

/* AFIO Registers */
typedef struct
{
    volatile uint32_t EVCR;
    volatile uint32_t MAPR;
    volatile uint32_t EXTICR[4];
    volatile uint32_t MAPR2;
}AFIO_Reg;

#define AFIO ((AFIO_Reg *) AFIO_BASE)

/* RCC Registers */
typedef struct
{
    volatile uint32_t CR;
    volatile uint32_t CFGR;
    volatile uint32_t CIR;
    volatile uint32_t APB2RSTR;
    volatile uint32_t APB1RSTR;
    volatile uint32_t AHBENR;
    volatile uint32_t APB2ENR;
    volatile uint32_t APB1ENR;
    volatile uint32_t BDCR;
    volatile uint32_t CSR;
    volatile uint32_t AHBSTR;
    volatile uint32_t CFGR2;
}RCC_Reg;

#define RCC ((RCC_Reg *) RCC_BASE)

/* EXTI Registers */
typedef struct 
{
    volatile uint32_t IMR;
    volatile uint32_t EMR;
    volatile uint32_t RTSR;
    volatile uint32_t FTSR;
    volatile uint32_t SWIER;
    volatile uint32_t PR;
}EXTI_Reg;

#define EXTI ((EXTI_Reg *) EXTI_BASE)

#define IRQ_NO_EXTI0       6
#define IRQ_NO_EXTI1       7
#define IRQ_NO_EXTI2       8
#define IRQ_NO_EXTI3       9
#define IRQ_NO_EXTI4       10
#define IRQ_NO_EXTI9_5     23
#define IRQ_NO_EXTI15_10   40

#define ENABLE 1
#define DISABLE 0
#define SET ENABLE
#define RESET DISABLE
#define GPIO_PIN_SET SET
#define GPIO_PIN_RESET RESET
#define FLAG_SET SET
#define FLAG_RESET RESET

#endif // _STM32F103_BASE_H_