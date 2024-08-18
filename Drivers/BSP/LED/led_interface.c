 /**
 * @note: Compiler: AC5 with -O3 optimization
 * @note: Standard: C99 tab-width: 4
 * @brief:   移植LED需提供的函数
 * @details: 移植LED需提供的函数，包括初始化、去初始化、点亮、熄灭、延时等功能。
 * @encoding: GBK
 * @date: 2024-07-23
 * @author: 刘禹材
 * @version: 1.0
 */
#include "led_interface.h"
#include "utils.h"

/**
 * @brief 初始化LED
 * @note  LED1-LED6 
 *        状态灯->PB2 告警灯->PB1 SOC1->PB0 
 *        SOC2->PC5   SOC3->PC4   SOC4->PA7
 * @param  
 * @return 
 */
uint8_t led_gpio_init(void)
{
    rcu_periph_clock_enable(RCU_GPIOA);
    rcu_periph_clock_enable(RCU_GPIOB);
    rcu_periph_clock_enable(RCU_GPIOC);
    GPIO_CTL0(GPIOB)&=~(0xFFF<<0);
    GPIO_CTL0(GPIOB)|=(0x01<<0);
    GPIO_CTL0(GPIOB)|=(0x01<<4);
    GPIO_CTL0(GPIOB)|=(0x01<<8);

    GPIO_CTL0(GPIOC)&=~(0xFF<<16);
    GPIO_CTL0(GPIOC)|=(0x01<<16);
    GPIO_CTL0(GPIOC)|=(0x01<<20);

    GPIO_CTL0(GPIOA)&=~(0xFUL<<28);
    GPIO_CTL0(GPIOA)|=(0x01<<28);


    return 0;
}
uint8_t led_gpio_deinit(void)
{
    return 0;
}
void led_write_pin(void *GPIOx, uint16_t GPIO_Pin, uint8_t state)
{
    uint32_t GPIOxAdapter = (uint32_t)GPIOx;
    uint32_t pinAdapter = (uint32_t)GPIO_Pin;
    gpio_bit_write(GPIOxAdapter, pinAdapter, (bit_status)state);
}
void led_delay_ms(uint32_t ms)
{
    delay_ms(ms);
}
void led_delay_us(uint32_t us)
{
    delay_us(us);
}