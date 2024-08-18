#ifndef BL5372_INTERFACE_H
#define BL5372_INTERFACE_H
#ifdef __cplusplus
extern "C" {
#endif

#include "BL5372_driver.h"
uint8_t BL5372_IIC_Init(void);
uint8_t BL5372_IIC_DeInit(void);
uint8_t BL5372_IIC_Read(uint8_t addr, uint8_t reg, uint8_t *buf, uint16_t len);
uint8_t BL5372_IIC_Write(uint8_t addr, uint8_t reg, uint8_t *buf, uint16_t len);
void BL5372_Debug_Print(const char *const fmt, ...);
#ifdef __cplusplus
}
#endif
#endif //BL5372_INTERFACE_H
