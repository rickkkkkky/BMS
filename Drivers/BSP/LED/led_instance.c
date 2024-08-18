 /**
 * @note: Compiler: AC5 with -O3 optimization
 * @note: Standard: C99 tab-width: 4
 * @brief: LED结构体实例化
 * @details: 
 * @encoding: GBK
 * @date: 2024-07-23
 * @author: 刘禹材
 * @version: 1.0
 */
#include "led_instance.h"
#include "led_interface.h"

static led_handle_t led_handle[6];

static void init(led_instance *led) 
{
    switch (led->id)
    {
        case 1:
        led->handle->GPIO_Pin=LED1_Pin;
        led->handle->GPIOx=(void *)LED1_GPIO_Port;
        break;
        case 2:
        led->handle->GPIO_Pin=LED2_Pin;
        led->handle->GPIOx=(void *)LED2_GPIO_Port;
        break;
        case 3:
        led->handle->GPIO_Pin=LED3_Pin;
        led->handle->GPIOx=(void *)LED3_GPIO_Port;
        break;
        case 4:
        led->handle->GPIO_Pin=LED4_Pin;
        led->handle->GPIOx=(void *)LED4_GPIO_Port;
        break;
        case 5:
        led->handle->GPIO_Pin=LED5_Pin;
        led->handle->GPIOx=(void *)LED5_GPIO_Port;
        break;
        case 6:
        led->handle->GPIO_Pin=LED6_Pin;
        led->handle->GPIOx=(void *)LED6_GPIO_Port;
        break;
        default:
        break;
    }
    led->handle->on_state=LED_SET;
    led->handle->GPIO_Init=led_gpio_init;
    led->handle->GPIO_DeInit=led_gpio_deinit;
    led->handle->GPIO_WritePin=led_write_pin;
    led->handle->delay_ms=led_delay_ms;
    led->handle->delay_us=led_delay_us;
    led_init(led->handle);
}

static void deinit(led_instance *led)
{

}   
static void on(led_instance *led)
{
    led_on(led->handle);
}
static void off(led_instance *led)
{
    led_off(led->handle);
}
static void toggle(led_instance *led)
{
    led_toggle(led->handle);
}
static void breath( led_instance *led,uint16_t period,uint8_t times)
{
    led_breath(led->handle,period,times);
}
void marquee()
{

}
led_instance LED_soc1=
{
    .id=3,
    .handle=&led_handle[2],
    .init=init,
    .deinit=deinit,
    .on=on,
    .off=off,
    .toggle=toggle,
    .breath=breath,
    // .fun={init,deinit,on,off,toggle}
};
led_instance LED_soc2=
{
    .id=4,
    .handle=&led_handle[3],
    .init=init,
    .deinit=deinit,
    .on=on,
    .off=off,
    .toggle=toggle,
    .breath=breath,
    // .fun={init,deinit,on,off,toggle}
};
led_instance LED_soc3=
{
    .id=5,
    .handle=&led_handle[4],
    .init=init,
    .deinit=deinit,
    .on=on,
    .off=off,
    .toggle=toggle,
    .breath=breath
    // .fun={init,deinit,on,off,toggle}
};
led_instance LED_soc4=
{
    .id=6,
    .handle=&led_handle[5],
    .init=init,
    .deinit=deinit,
    .on=on,
    .off=off,
    .toggle=toggle,
    .breath=breath,
    // .fun={init,deinit,on,off,toggle}
};
led_instance LED_alert=
{
    .id=2,
    .handle=&led_handle[1],
    .init=init,
    .deinit=deinit,
    .on=on,
    .off=off,
    .toggle=toggle,
    .breath=breath,
    // .fun={init,deinit,on,off,toggle}
};
led_instance LED_state=
{
    .id=1,
    .handle=&led_handle[0],
    .init=init,
    .deinit=deinit,
    .on=on,
    .off=off,
    .toggle=toggle,
    .breath=breath,
    // .fun={init,deinit,on,off,toggle}
};
/**
 * @note 只有4个灯 所以电量显示为4档 0 25 50 75 100
 * @param soc 18代表百分之18的电量
 */
// void led_show_soc(float soc)
// {
//     if(soc<10)
//     {
//         led2.off(&led2);
//         led3.off(&led3);
//         led4.off(&led4);
//         led5.off(&led5);
//     }

//     if(soc>=10 && soc<=25)
//     {
//         led2.on(&led2);
//         led3.off(&led3);
//         led4.off(&led4);
//         led5.off(&led5);
//     }
//     else if(soc>25 && soc<=50)
//     {
//         led2.on(&led2);
//         led3.on(&led3);
//         led4.off(&led4);
//         led5.off(&led5);
//     }
//     else if(soc>50 && soc<=75)
//     {
//         led2.on(&led2);
//         led3.on(&led3);
//         led4.on(&led4);
//         led5.off(&led5);
//     }
//     else if(soc>75 && soc<=100)
//     {
//         led2.on(&led2);
//         led3.on(&led3);
//         led4.on(&led4);
//         led5.on(&led5);
//     }

// }