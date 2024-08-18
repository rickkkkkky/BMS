#include"main.h"
#include "utils.h"
#define ADC_DATABUFFSZ 5
static uint16_t adc_value[ADC_DATABUFFSZ];
static void dma_config(void)
{
    /* enable DMA0 clock */
    rcu_periph_clock_enable(RCU_DMA0);
    /* ADC_DMA_channel configuration */
    dma_parameter_struct dma_data_parameter;
    
    /* ADC DMA_channel configuration */
    dma_deinit(DMA0, DMA_CH0);
    
    /* initialize DMA single data mode */
    dma_data_parameter.periph_addr  = (uint32_t)(&ADC_RDATA(ADC0));
    dma_data_parameter.periph_inc   = DMA_PERIPH_INCREASE_DISABLE;      //外设地址不递增
    dma_data_parameter.memory_addr  = (uint32_t)(&adc_value);
    dma_data_parameter.memory_inc   = DMA_MEMORY_INCREASE_ENABLE;       //内存地址递增
    dma_data_parameter.periph_width = DMA_PERIPHERAL_WIDTH_16BIT;
    dma_data_parameter.memory_width = DMA_MEMORY_WIDTH_16BIT;  
    dma_data_parameter.direction    = DMA_PERIPHERAL_TO_MEMORY;
    dma_data_parameter.number       = ADC_DATABUFFSZ;
    dma_data_parameter.priority     = DMA_PRIORITY_HIGH;
    dma_init(DMA0, DMA_CH0, dma_data_parameter);

    dma_circulation_enable(DMA0, DMA_CH0);
  
    /* enable DMA channel */
    dma_channel_enable(DMA0, DMA_CH0);
}

void ADC_Init(void)
{
    rcu_periph_clock_enable(RCU_GPIOA);
    rcu_periph_clock_enable(RCU_GPIOC);
    gpio_init(GPIOA, GPIO_MODE_AIN, GPIO_OSPEED_10MHZ, GPIO_PIN_6);         //T MOS
    gpio_init(GPIOC, GPIO_MODE_AIN, GPIO_OSPEED_10MHZ, GPIO_PIN_0);         //TS1
    gpio_init(GPIOC, GPIO_MODE_AIN, GPIO_OSPEED_10MHZ, GPIO_PIN_1);         //TS2
    gpio_init(GPIOC, GPIO_MODE_AIN, GPIO_OSPEED_10MHZ, GPIO_PIN_2);         //TS3
    gpio_init(GPIOC, GPIO_MODE_AIN, GPIO_OSPEED_10MHZ, GPIO_PIN_3);         //TS4

    dma_config();
    /* enable ADC clock */
    rcu_periph_clock_enable(RCU_ADC0);

    /* config ADC clock 120MHz/6=20MHz*/
    rcu_adc_clock_config(RCU_CKADC_CKAPB2_DIV6);

        /* ADC mode config */
    adc_mode_config(ADC_MODE_FREE); 
    /* ADC continuous function enable */
    adc_special_function_config(ADC0, ADC_CONTINUOUS_MODE, ENABLE);     //连续采样模式
    /* ADC scan function enable */
    adc_special_function_config(ADC0, ADC_SCAN_MODE, ENABLE);           //扫描模式
    /* ADC data alignment config */
    adc_data_alignment_config(ADC0, ADC_DATAALIGN_RIGHT);               //右对齐

    /* ADC channel length config */
    adc_channel_length_config(ADC0, ADC_REGULAR_CHANNEL, 5);           //ADC通道数为5

    /* ADC regular channel config */ 
    /*2.85us一次*/
    adc_regular_channel_config(ADC0, 0, ADC_CHANNEL_10, ADC_SAMPLETIME_55POINT5);   //通道10第1次采集
    adc_regular_channel_config(ADC0, 1, ADC_CHANNEL_11, ADC_SAMPLETIME_55POINT5);   //通道11第2次采集
    adc_regular_channel_config(ADC0, 2, ADC_CHANNEL_12, ADC_SAMPLETIME_55POINT5);
    adc_regular_channel_config(ADC0, 3, ADC_CHANNEL_13, ADC_SAMPLETIME_55POINT5);
    adc_regular_channel_config(ADC0, 4, ADC_CHANNEL_6, ADC_SAMPLETIME_55POINT5);
    
    /* ADC trigger config */
    /* 外部触发源配置 */
    adc_external_trigger_source_config(ADC0, ADC_REGULAR_CHANNEL, ADC0_1_2_EXTTRIG_REGULAR_NONE);
    /* 外部触发使能 */
    adc_external_trigger_config(ADC0, ADC_REGULAR_CHANNEL, ENABLE);

    /* ADC DMA function enable */
    adc_dma_mode_enable(ADC0);
    /* enable ADC interface */
    adc_enable(ADC0);
    delay_ms(1);
    /* ADC calibration and reset calibration */
    adc_calibration_enable(ADC0);

    /* ADC software trigger enable */
    adc_software_trigger_enable(ADC0, ADC_REGULAR_CHANNEL);

}
void ADC_get_Data()
{
    for(uint16_t i = 0; i < ADC_DATABUFFSZ; i++)
    {
        // usart_transmit_buffer(USART1, (uint8_t*)&adc_value[i], 2);
        UART_Printf(UART3,"ADC%d:%d\n", i, adc_value[i]);
        // UART_Printf(UART3,"ADC%d:%d\n", i, ADC_RDATA(ADC0));
        // delay_ms(10);
        // while(ADC_STAT(ADC0)&(1<<1));
    }
  
}
