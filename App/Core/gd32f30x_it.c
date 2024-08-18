/**
 * @note: Compiler: AC5 with -O3 optimization
 * @note: Standard: C99 tab-width: 4
 * @brief: 中断服务函数文件
 * @details:
 * @encoding: UTF-8
 * @date: 2024-07-23
 * @author: 刘禹材
 * @version: 1.0
 */
// #include "gd32f30x_it.h"
#include <string.h>
#include "global.h"
#include "main.h"
#include "utils.h"
#include "RS485_instance.h"
void TIMER5_IRQHandler(void)
{
    g_runtime_ms++;
    if (g_runtime_ms % 1000 == 0)
    {
        g_runtime_s++;
    }
    timer_interrupt_flag_clear(TIMER5, TIMER_INT_FLAG_UP);
}
void USART2_IRQHandler(void)
{
    // uint8_t data;
    if(USART_STAT0(USART2)&(1<<5))
    {
        USART_STAT0(USART2) &= ~(1<<5);
    }
    if(USART_STAT0(USART2)&(1<<4))
    {
        dma_channel_disable(DMA0, DMA_CH2);

        g_Rx2Bufsz = RX2_BUFFER_SIZE - (dma_transfer_number_get(DMA0, DMA_CH2));
        // RS485_DataCopy( g_rx2_buffer,g_Rx2Bufsz);
        // for(uint16_t i = 0; i < g_Rx2Bufsz; i++)
        // {
        //    UART_Printf(USART2 , "%x", g_rx2_buffer[i]);
        // }
        // UART_Printf(USART2, "\r\n");

        memset( g_rx2_buffer, 0, sizeof(g_rx2_buffer));
        g_Rx2Bufsz = 0;

        /* disable DMA and reconfigure */
        dma_transfer_number_config(DMA0, DMA_CH2, RX2_BUFFER_SIZE);
        dma_channel_enable(DMA0, DMA_CH2);
        USART_STAT0(USART2) &= ~(1<<4);
        USART_DATA(USART2);
        USART_STAT0(USART2);
    }
}
void UART3_IRQHandler(void)
{
    // uint8_t data;
    // if (SET == usart_interrupt_flag_get(UART3, USART_INT_FLAG_IDLE))
    // if(USART_STAT0(UART3)&(1<<5))
    // {
    //     data=USART_DATA(UART3);
    //     g_rx3_buffer[g_Rx3Bufsz++] = data;
    //     USART_STAT0(UART3) &= ~(1<<5);
    //     // usart_flag_clear(UART3, USART_INT_RBNE);
    // }
    if(USART_STAT0(UART3)&(1<<4))
    {
        dma_channel_disable(DMA1, DMA_CH2);
        g_Rx3Bufsz = RX3_BUFFER_SIZE - (dma_transfer_number_get(DMA1, DMA_CH2));
        
        // UART_Printf(UART3, "receive data:%d\n", g_Rx3Bufsz);
        RS485_DataCopy( g_rx3_buffer,g_Rx3Bufsz);
        // for(uint16_t i = 0; i < g_Rx3Bufsz; i++)
        // {
        //    UART_Printf(UART3 , "%x", g_rx3_buffer[i]);
        // }
        // UART_Printf(UART3, "\r\n");
        memset( g_rx3_buffer, 0, sizeof(g_rx3_buffer));
        g_Rx3Bufsz = 0;
        USART_STAT0(UART3) &= ~(1<<4);
        USART_DATA(UART3);
        USART_STAT0(UART3);
        /* disable DMA and reconfigure */
        dma_transfer_number_config(DMA1, DMA_CH2, RX3_BUFFER_SIZE);
        dma_channel_enable(DMA1, DMA_CH2);
    }
}