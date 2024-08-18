#pragma once
#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include "main.h"
//delay.c中定义
uint32_t GetRunTime_ms(void);
uint32_t GetRunTime_s (void);
void     delay_ms     (uint32_t ms);
void     delay_us     (uint32_t us);
//uart_printf.c中定义
void usart_transmit_buffer(uint32_t usart_periph, uint8_t *buffer, uint16_t length);
void UART_Printf          (uint32_t usart_periph, const char *format, ...) ;
//
#ifdef __cplusplus
}
#endif



