#ifndef BL5372_DRIVER_H
#define BL5372_DRIVER_H

#ifdef __cplusplus
extern "C" {
#endif
#include <stdint.h>

// BL5372 寄存器定义
#define BL5372_REG_SECOND           0x00 // 0H 秒寄存器 以 BCD 码形式计数与存储秒
#define BL5372_REG_MINUTE           0x01 // 1H 分寄存器 以 BCD 码形式计数与存储分
#define BL5372_REG_HOUR             0x02 // 2H 时寄存器 以 BCD 码形式计数与存储时
#define BL5372_REG_WEEKDAY          0x03 // 3H 周寄存器 以 BCD 码形式计数与存储周
#define BL5372_REG_DAY              0x04 // 4H 天寄存器 以 BCD 码形式计数与存储天
#define BL5372_REG_MONTH            0x05 // 5H 月寄存器 以 BCD 码形式计数与存储月
#define BL5372_REG_YEAR             0x06 // 6H 年寄存器 以 BCD 码形式计数与存储年
#define BL5372_REG_ADJUST           0x07 // 7H 时间调整 存储晶振的修正参数及外部晶振选择控制
#define BL5372_REG_TIMERA_MINUTE    0x08 // 8H 分定时 A 存储定时器 A 分的数据
#define BL5372_REG_TIMERA_HOUR      0x09 // 9H 时定时 A 存储定时器 A 时的数据
#define BL5372_REG_TIMERA_WEEKDAY   0x0A // AH 天定时 A 存储定时器 A 星期的数据
#define BL5372_REG_TIMERB_MINUTE    0x0B // BH 分定时 B 存储定时器 B 分的数据
#define BL5372_REG_TIMERB_HOUR      0x0C // CH 时定时 B 存储定时器 B 时的数据
#define BL5372_REG_TIMERB_WEEKDAY   0x0D // DH 天定时 B 存储定时器 B 星期的数据
#define BL5372_REG_CONTROL1         0x0E // EH 控制 1 存储响铃使能、中断输出口选择、周期性中断的周期选择
#define BL5372_REG_CONTROL2         0x0F // FH 控制 2 存储时间显示选择、中断与报时标志、停振检测

typedef struct 
{
    uint8_t iic_addr;                                                                              
    uint8_t (*iic_init)(void);                                                                     
    uint8_t (*iic_deinit)(void);                                                                   
    uint8_t (*iic_read)(uint8_t addr, uint8_t reg, uint8_t *buf, uint16_t len);                    
    uint8_t (*iic_write)(uint8_t addr, uint8_t reg, uint8_t *buf, uint16_t len);                       
    // void (*delay_ms)(uint32_t ms);                                                         
    void (*debug_print)(const char *const fmt, ...);                                                                                                                                
    uint8_t inited;                                                                                
}bl5372_handle_t;


typedef enum
{
    BL5372_sunday=0,
    BL5372_monday ,
    BL5372_tuesday,
    BL5372_wednesday,
    BL5372_thursday,
    BL5372_friday,
    BL5372_saturday,
    
}BL5372_week_day_t;

uint8_t BL5372_Init(bl5372_handle_t *handle);
uint8_t BL5372_get_RTC(bl5372_handle_t *handle, uint8_t *buf, uint8_t len);
uint8_t BL5372_set_RTC(bl5372_handle_t *handle, uint8_t *buf, uint8_t len);
#ifdef __cplusplus
}
#endif
#endif /* BL5372_DRIVER_H */
