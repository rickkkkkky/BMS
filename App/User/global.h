#pragma once
#include <stdint.h>
//MD 0-1
// 00： 输入模式（复位状态）
// 01： 输出模式，最大速度 10MHz
// 10： 输出模式，最大速度 2MHz
// 11： 输出模式，最大速度 50MHz
//CTL 2-3
// 输入模式（MD[1:0] = 00）
// 00： 模拟输入
// 01： 浮空输入
// 10： 上拉输入/下拉输入
// 11： 保留
// 输出模式（MD[1:0] > 00）
// 00： GPIO 推挽输出
// 01： GPIO 开漏输出
// 10： AFIO 推挽输出
// 11： AFIO 开漏输出
#define RX2_BUFFER_SIZE 260
#define RX3_BUFFER_SIZE 260

extern uint8_t g_rx2_buffer[RX3_BUFFER_SIZE];
extern uint16_t g_Rx2Bufsz;

extern uint8_t g_rx3_buffer[RX2_BUFFER_SIZE];
extern uint16_t g_Rx3Bufsz;

extern volatile uint32_t g_runtime_ms ;
extern volatile uint32_t g_runtime_s  ;   
