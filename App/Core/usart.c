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

#include "main.h"
#include "global.h"
void usart2_dma_config(void)
{
    dma_parameter_struct dma_init_struct;
    
    rcu_periph_clock_enable(RCU_DMA0);
    
    dma_deinit(DMA0, DMA_CH2);
    dma_init_struct.direction = DMA_PERIPHERAL_TO_MEMORY;
    dma_init_struct.memory_addr = (uint32_t)g_rx2_buffer;
    dma_init_struct.memory_inc = DMA_MEMORY_INCREASE_ENABLE;
    dma_init_struct.memory_width = DMA_MEMORY_WIDTH_8BIT;
    dma_init_struct.number = RX2_BUFFER_SIZE;
    dma_init_struct.periph_addr = (uint32_t)(&USART_DATA(USART2));
    dma_init_struct.periph_inc = DMA_PERIPH_INCREASE_DISABLE;
    dma_init_struct.periph_width = DMA_PERIPHERAL_WIDTH_8BIT;
    dma_init_struct.priority = DMA_PRIORITY_ULTRA_HIGH;
    dma_init(DMA0, DMA_CH2, dma_init_struct);
   
    dma_circulation_disable(DMA0, DMA_CH2);
   
    dma_channel_enable(DMA0, DMA_CH2);
}
void usart2_init(void )
{
    usart2_dma_config();

    rcu_periph_clock_enable(RCU_GPIOA);

    rcu_periph_clock_enable(RCU_USART2);
    
   
    gpio_init(GPIOA, GPIO_MODE_AF_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_2);   
    gpio_init(GPIOA, GPIO_MODE_IN_FLOATING, GPIO_OSPEED_50MHZ, GPIO_PIN_3);

    usart_deinit(USART2);
    usart_baudrate_set(USART2, 9600U);
    
    usart_receive_config(USART2, USART_RECEIVE_ENABLE);
    usart_transmit_config(USART2, USART_TRANSMIT_ENABLE);
    usart_dma_receive_config(USART2, USART_DENR_ENABLE);

    usart_interrupt_enable(USART2, USART_INT_IDLE);
    
    usart_enable(USART2);

}
void uart3_dma_config(void)
{
    dma_parameter_struct dma_init_struct;
    
    rcu_periph_clock_enable(RCU_DMA1);
    
    dma_deinit(DMA1, DMA_CH2);
    dma_init_struct.direction = DMA_PERIPHERAL_TO_MEMORY;
    dma_init_struct.memory_addr = (uint32_t)g_rx3_buffer;
    dma_init_struct.memory_inc = DMA_MEMORY_INCREASE_ENABLE;
    dma_init_struct.memory_width = DMA_MEMORY_WIDTH_8BIT;
    dma_init_struct.number = RX3_BUFFER_SIZE;
    dma_init_struct.periph_addr = (uint32_t)(&USART_DATA(UART3));
    dma_init_struct.periph_inc = DMA_PERIPH_INCREASE_DISABLE;
    dma_init_struct.periph_width = DMA_PERIPHERAL_WIDTH_8BIT;
    dma_init_struct.priority = DMA_PRIORITY_ULTRA_HIGH;
    dma_init(DMA1, DMA_CH2, dma_init_struct);
   
    dma_circulation_disable(DMA1, DMA_CH2);
   
    dma_channel_enable(DMA1, DMA_CH2);
}
void uart3_init(void )
{
    uart3_dma_config();

    rcu_periph_clock_enable(RCU_GPIOC);
    rcu_periph_clock_enable(RCU_UART3);
    
   
    gpio_init(GPIOC, GPIO_MODE_AF_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_10);   
    gpio_init(GPIOC, GPIO_MODE_IN_FLOATING, GPIO_OSPEED_50MHZ, GPIO_PIN_11);

    usart_deinit(UART3);
    usart_baudrate_set(UART3, 115200U);
    
    usart_receive_config(UART3, USART_RECEIVE_ENABLE);
    usart_transmit_config(UART3, USART_TRANSMIT_ENABLE);
    usart_dma_receive_config(UART3, USART_DENR_ENABLE);

    usart_interrupt_enable(UART3, USART_INT_IDLE);
    
    usart_enable(UART3);
}






