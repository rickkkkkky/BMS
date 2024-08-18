#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif
#include "gd32f30x_libopt.h"
#include "iic_interface.h"

#define LED6_Pin            GPIO_PIN_7
#define LED6_GPIO_Port      GPIOA
#define LED5_Pin            GPIO_PIN_4
#define LED5_GPIO_Port      GPIOC
#define LED4_Pin            GPIO_PIN_5
#define LED4_GPIO_Port      GPIOC
#define LED3_Pin            GPIO_PIN_0
#define LED3_GPIO_Port      GPIOB
#define LED2_Pin            GPIO_PIN_1
#define LED2_GPIO_Port      GPIOB
#define LED1_Pin            GPIO_PIN_2
#define LED1_GPIO_Port      GPIOB

#define SDA1_Pin            GPIO_PIN_12
#define SDA1_GPIO_Port      GPIOB
#define SCL1_Pin            GPIO_PIN_13
#define SCL1_GPIO_Port      GPIOB

#define RS485_RE_Pin        GPIO_PIN_2
#define RS485_RE_GPIO_Port  GPIOA
//iic.c中定义
extern iic_bus IIC[2];
void TIM5_Init(void);
void usart2_init(void);
void uart3_init(void);
void ADC_Init(void);
void ADC_get_Data();
#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
