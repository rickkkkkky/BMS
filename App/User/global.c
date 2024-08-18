 /**
 * @note: Compiler: AC5 with -O3 optimization
 * @note: Standard: C99 tab-width: 4
 * @brief: 全局变量定义
 * @details: 
 * @encoding: UTF-8
 * @date: 2024-07-23
 * @author: 刘禹材
 * @version: 1.0
 */
#include <stdint.h>
#include "global.h"
volatile uint32_t g_runtime_ms = 0;
volatile uint32_t g_runtime_s  = 0;   
uint8_t g_rx2_buffer[RX2_BUFFER_SIZE];
uint16_t g_Rx2Bufsz = 0;

uint8_t g_rx3_buffer[RX3_BUFFER_SIZE];
uint16_t g_Rx3Bufsz = 0;


// uint8_t g_rx2_buffer[RX4_BUFFER_SIZE];
// uint8_t g_rx5_buffer[RX5_BUFFER_SIZE];