#include "BL5372_instance.h"
static bl5372_handle_t bl5372;
void bl5372_basic_init(void)
{
    bl5372.iic_addr = BL5372_I2C_ADDR;
    bl5372.debug_print=BL5372_Debug_Print;
    bl5372.iic_init=BL5372_IIC_Init;
    bl5372.iic_deinit=BL5372_IIC_DeInit;
    bl5372.iic_read=BL5372_IIC_Read;
    bl5372.iic_write=BL5372_IIC_Write;
    BL5372_Init(&bl5372);
}
void bl5372_get_RTC(uint8_t *buf, uint8_t len)
{
    BL5372_get_RTC(&bl5372,buf,len);
}
void bl5372_set_RTC(uint8_t *buf, uint8_t len)
{
    BL5372_set_RTC(&bl5372,buf,len);
}