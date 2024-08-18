#include "BL5372_interface.h"
#include "iic_interface.h"
#include "main.h"

uint8_t BL5372_IIC_Init(void)
{
    IIC[1].GPIO_Init();
    return 0;
}

uint8_t BL5372_IIC_DeInit(void)
{
    return 0;
}

uint8_t BL5372_IIC_Read(uint8_t addr, uint8_t reg, uint8_t *buf, uint16_t len)
{
    __disable_irq();
    IIC_Read_Multi_Byte(&IIC[1], addr, reg, buf, len);
    __enable_irq();
    return 0;
}

uint8_t BL5372_IIC_Write(uint8_t addr, uint8_t reg, uint8_t *buf, uint16_t len)
{
    __disable_irq();
    IIC_Write_Multi_Byte(&IIC[1], addr, reg, buf, len);
    __enable_irq();
    return 0 ;
}
// void BL5372_Delay_MS(uint32_t ms)
// {
//     delay_ms(ms);
// }
void BL5372_Debug_Print(const char *const fmt, ...)
{

}
