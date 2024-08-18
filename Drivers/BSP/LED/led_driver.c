#include "led_driver.h"
#define NULL 0
uint8_t led_init(led_handle_t *handle)
{
    if( handle == NULL)
        return 1;
    if( handle->GPIO_Init == NULL || handle->GPIO_WritePin == NULL || handle->GPIO_DeInit == NULL|| 
        handle->delay_us  == NULL || handle->delay_ms      == NULL                                  )   
        return 2;
    handle->GPIO_Init();
    handle->inited=1;
    return 0;
}
uint8_t led_on(led_handle_t *handle)
{
    if (handle->on_state == LED_SET)
        handle->GPIO_WritePin(handle->GPIOx, handle->GPIO_Pin, LED_SET);
    else
        handle->GPIO_WritePin(handle->GPIOx, handle->GPIO_Pin, LED_RESET);
    handle->state = 1;
    return 0;
}
uint8_t led_off(led_handle_t *handle)
{
    if (handle->on_state == LED_SET)
        handle->GPIO_WritePin(handle->GPIOx, handle->GPIO_Pin, LED_RESET);
    else
        handle->GPIO_WritePin(handle->GPIOx, handle->GPIO_Pin, LED_SET);
    handle->state = 0;
    return 0;
}
uint8_t led_toggle(led_handle_t *handle)
{

    if (handle->state == 1)
        led_off(handle);
    else
        led_on(handle);
    return 0;
}
/**
 * @brief breathing effect
 * @param handle: led handle
 * @param period: period of breathing effect ????ms
 * @param times: number of times to repeat the breathing effect
 * @return 0
 */
uint8_t led_breath(led_handle_t *handle, uint16_t period,uint8_t times)
{
    while(times-->0)
    {
        for(uint16_t i=1;i<period/2;i++)
        {
            led_on(handle);
            handle->delay_us(i);
            led_off(handle);
            handle->delay_us(period/2-i);
        }
        for(uint16_t i=period/2;i>1;i--)
        {
            led_on(handle);
            handle->delay_us(i);
            led_off(handle);
            handle->delay_us(period/2-i);
        }

    }
    return 0;
}

// void led_marquee(led_handle_t *handles, uint8_t num_leds, uint32_t ms) 
// {
//     for (uint8_t i = 0; i < num_leds; i++) 
//     {
//         led_on(&handles[i]);
//         handles->delay_ms(ms);

//         led_off(&handles[i]);
//     }
// }