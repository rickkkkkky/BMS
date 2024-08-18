#ifndef __BL5372_INSTANCE_H__
#define __BL5372_INSTANCE_H__
#ifdef __cplusplus
extern "C" {
#endif
#include "BL5372_interface.h"
#define BL5372_I2C_ADDR             0x64 // BL5372 I2C 地址

void bl5372_basic_init(void);
void bl5372_get_RTC(uint8_t *buf, uint8_t len);
void bl5372_set_RTC(uint8_t *buf, uint8_t len);
#ifdef __cplusplus
}
#endif

#endif // __BL5372_INSTANCE_H__