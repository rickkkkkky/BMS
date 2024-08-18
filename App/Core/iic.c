#include "iic.h"
#include "main.h"
#include "utils.h"
/**
 * @brief PA4 is SDA and PA5 is SCL
 * @note  只负责和SH76930通信
 * @param
 */
static uint8_t IIC_Init(void)
{
    rcu_periph_clock_enable(RCU_GPIOA);
    gpio_init(GPIOA, GPIO_MODE_OUT_OD, GPIO_OSPEED_50MHZ, GPIO_PIN_4); 
    gpio_init(GPIOA, GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_5); 
    return 0;
}
/**
 * @brief PB12 is SDA1 and PB13 is SCL1
 * @note  负责和EEPROM和BL5372通信
 * @param
 */
static uint8_t IIC1_Init(void)
{
    rcu_periph_clock_enable(RCU_GPIOB);
    gpio_init(GPIOB, GPIO_MODE_OUT_OD, GPIO_OSPEED_50MHZ, GPIO_PIN_12); 
    gpio_init(GPIOB, GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_13); 
    return 0;
}
static uint8_t IIC_DeInit(void)
{
    return 0;
}
static void IIC_write_pin(void *GPIOx, uint16_t GPIO_Pin, uint8_t state)
{
    uint32_t GPIOxAdapter = (uint32_t)GPIOx;
    uint32_t pinAdapter = (uint32_t)GPIO_Pin;
    gpio_bit_write(GPIOxAdapter, pinAdapter, (bit_status)state);
}
static uint8_t IIC_read_pin(void *GPIOx, uint16_t GPIO_Pin)
{
    uint32_t GPIOxAdapter = (uint32_t)GPIOx;
    uint32_t pinAdapter = (uint32_t)GPIO_Pin;
    return (uint8_t)gpio_input_bit_get(GPIOxAdapter, pinAdapter);
}
iic_bus IIC[2] = {
    {
        .inited = 0,
        .lock = 0,
        .GPIO_Init = IIC_Init,
        .GPIO_DeInit = IIC_DeInit,
        .GPIOx_SDA = (void *)GPIOA,
        .GPIOx_SCL = (void *)GPIOA,
        .GPIO_SDA_Pin = GPIO_PIN_4,
        .GPIO_SCL_Pin = GPIO_PIN_5,
        .GPIO_WritePin = IIC_write_pin,
        .GPIO_ReadPin = IIC_read_pin,
        .delay_us = delay_us,
        .delay_start_condition = 5,
        .delay_after_sda_change = 5,
    },
    {
        .inited = 0,
        .lock = 0,
        .GPIO_Init = IIC1_Init,
        .GPIO_DeInit = IIC_DeInit,
        .GPIOx_SDA = (void *)GPIOB,
        .GPIOx_SCL = (void *)GPIOB,
        .GPIO_SDA_Pin = GPIO_PIN_12,
        .GPIO_SCL_Pin = GPIO_PIN_13,
        .GPIO_WritePin = IIC_write_pin,
        .GPIO_ReadPin = IIC_read_pin,
        .delay_us = delay_us,
        .delay_start_condition = 5,
        .delay_after_sda_change = 5,

    }

};
