#ifndef __SLAVE_H
#define __SLAVE_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include "agile_modbus.h"
#include "agile_modbus_slave_util.h"
#ifndef NULL
#define NULL  (void*)0
#endif // !NULL
// extern pthread_mutex_t slave_mtx;
extern const agile_modbus_slave_util_t slave_util;
extern uint16_t _tab_registers[10];
extern uint16_t _tab_input_registers[10];
void *rtu_entry(void *param);
#ifdef __cplusplus
}
#endif

#endif /* __SLAVE_H */
