#ifndef _RS485_INSTANCE_H
#define _RS485_INSTANCE_H

#ifdef __cplusplus
extern "C" {
#endif
#include <stdint.h>
void RS485_Init(void);
void RS485_DataCopy(uint8_t *data, uint16_t len);
void RS485_RespondTask(void);
#ifdef __cplusplus
}
#endif
#endif /*_RS485_INSTANCE_H*/ 
