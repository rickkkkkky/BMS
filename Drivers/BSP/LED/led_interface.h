#ifndef _LED_INTERFACE_H
#define _LED_INTERFACE_H

#include <stdint.h>
#include "main.h"
// #include "gd32f30x_gpio.h"

#ifdef __cplusplus
extern "C" {
#endif


uint8_t led_gpio_init(void);
uint8_t led_gpio_deinit(void);
void    led_write_pin(void* GPIOx,uint16_t GPIO_Pin,uint8_t state);
void    led_delay_ms(uint32_t ms);
void    led_delay_us(uint32_t us);


#ifdef __cplusplus
}
#endif

#endif // !_LED_INTERFACE_H
