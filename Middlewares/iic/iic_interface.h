#ifndef _IIC_INTERFACE_H
#define _IIC_INTERFACE_H
#ifdef __cplusplus  
extern "C" {  
#endif  
#include <stdint.h>

#define IIC_DEBUG_ENABLED


typedef struct {  
    uint8_t  inited;
    uint8_t  lock  ; 
    void*    GPIOx_SDA;
    void*    GPIOx_SCL; 
    uint16_t GPIO_SDA_Pin;  
    uint16_t GPIO_SCL_Pin;  
    uint8_t  (*GPIO_Init)           (void);
    uint8_t  (*GPIO_DeInit)         (void);
    void     (*delay_us)            (uint32_t us);
    void     (*GPIO_WritePin)       (void* GPIOx,uint16_t GPIO_Pin,uint8_t state);
    uint8_t  (*GPIO_ReadPin)        (void* GPIOx,uint16_t GPIO_Pin);
    uint8_t  delay_start_condition; 
    uint8_t  delay_after_sda_change;
} iic_bus;

// uint8_t IICInit(iic_bus *bus);

uint8_t IIC_Write_One_Byte(iic_bus *bus, uint8_t addr, uint8_t reg, uint8_t data);
uint8_t IIC_Write_Multi_Byte(iic_bus *bus, uint8_t addr, uint8_t reg, uint8_t *data, uint16_t length);
uint8_t IIC_Read_One_Byte(iic_bus *bus, uint8_t addr, uint8_t reg);
uint8_t IIC_Read_Multi_Byte(iic_bus *bus, uint8_t addr, uint8_t reg, uint8_t *data, uint16_t length);
uint8_t IIC_check_device(iic_bus *bus,uint8_t addr);

uint8_t IIC_Read_Multi_Byte_16Reg_Addr( iic_bus *bus, uint8_t addr, uint16_t reg,   
                                        uint8_t *data, uint16_t length);
uint8_t IIC_Write_Multi_Byte_16Reg_Addr( iic_bus *bus, uint8_t addr, uint16_t reg,
                                         uint8_t *data, uint16_t length);
#ifdef __cplusplus  
}  
#endif
#endif //!_IIC_INTERFACE_H
