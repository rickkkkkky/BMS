#ifndef _LED_INSTANCE_H
#define _LED_INSTANCE_H

#include <stdint.h>
#include "led_driver.h"

#ifdef __cplusplus  
extern "C" {  
#endif  

typedef struct led_struct led_instance;
// typedef void (*led_fun)(led_instance *led);
typedef struct led_struct 
{
    uint8_t         id;
    led_handle_t    *handle;
    void (*init)    (led_instance*);
    void (*deinit)  (led_instance*);
    void (*on)      (led_instance*);
    void (*off)     (led_instance*);
    void (*toggle)  (led_instance*);
    void (*breath)  (led_instance*, uint16_t period,   uint8_t times );
    void (*marquee) (led_instance*, uint8_t  num_leds, uint32_t ms   );
} led_instance;

extern led_instance LED_soc1;
extern led_instance LED_soc2;
extern led_instance LED_soc3;
extern led_instance LED_soc4;
extern led_instance LED_alert;
extern led_instance LED_state;

#ifdef __cplusplus  
}
#endif  

#endif // !_LED_INSTANCE_H
