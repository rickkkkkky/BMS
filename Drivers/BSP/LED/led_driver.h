#ifndef _LED_DRIVER_H
#define _LED_DRIVER_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif
//LED高电平亮还是低电平亮
typedef enum 
{
    LED_RESET = 0,
    LED_SET   = 1,
}led_on_state_t;
typedef struct 
{
    uint8_t         state;
    led_on_state_t  on_state;
    uint8_t         inited;
    uint8_t         lock  ; 
    void*           GPIOx;
    uint16_t        GPIO_Pin;  
    uint8_t         (*GPIO_Init)           (void);
    uint8_t         (*GPIO_DeInit)         (void);
    void            (*GPIO_WritePin)       (void* GPIOx,uint16_t GPIO_Pin,uint8_t state);
    void            (*delay_us)            (uint32_t us);
    void            (*delay_ms)            (uint32_t ms);
}led_handle_t;
uint8_t led_init(led_handle_t *handle);
uint8_t led_on(led_handle_t *handle);
uint8_t led_off(led_handle_t *handle);
uint8_t led_toggle(led_handle_t *handle);
uint8_t led_breath(led_handle_t *handle, uint16_t period,uint8_t times);

#ifdef __cplusplus
}
#endif

#endif // !_LED_DRIVER_H
