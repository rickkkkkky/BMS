 /**
 * @note: Compiler: AC5 with -O3 optimization
 * @note: Standard: C99 tab-width: 4
 * @brief: 
 * @details: 
 * @encoding: UTF-8
 * @date: 2024-07-23
 * @author: 刘禹材
 * @version: 1.0
 */
#include <stdarg.h>  
#include <string.h>  
#include <stdio.h>  
#include "utils.h"
#include "main.h"
void usart_transmit_buffer(uint32_t usart_periph,uint8_t *buffer, uint16_t length)
{
    while (length-->0)
    {
        usart_data_transmit(usart_periph,*buffer++);
        while(RESET == usart_flag_get(usart_periph, USART_FLAG_TBE));
    }
}
void UART_Printf(uint32_t usart_periph, const char *format, ...) 
{
    char buffer[256];
    va_list args;
    va_start(args, format);
    vsprintf(buffer, format, args);
    va_end(args);

    usart_transmit_buffer(usart_periph, (uint8_t *)buffer, strlen(buffer));
}