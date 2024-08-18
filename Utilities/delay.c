 /**
 * @note: Compiler: AC5 with -O3 optimization
 * @note: Standard: C99 tab-width: 4
 * @brief: 
 * @details: 
 * @encoding: UTF-8
 * @date: 2024-07-23
 * @author: 刘禹材
 * @version: 1.0
 */
#include "utils.h"
#include "global.h"
#include "main.h"

/**
 * @brief: 获取当前运行时间ms
 */
uint32_t GetRunTime_ms(void)
{
    return g_runtime_ms;
}
/**
 * @brief: 获取当前运行时间s
 */
uint32_t GetRunTime_s(void)
{
    return g_runtime_s;
}

/**
 * @brief us延时 注意传参不要超过1000-1
 * @param us 
 */
void delay_us(uint32_t us)
{
    uint32_t start_time, end_time;
    start_time = timer_counter_read(TIMER5);
    while(1)
    {
        end_time = timer_counter_read(TIMER5);
        if((end_time - start_time) >= us)
        {
            break;
        }
    }
}
/**
 * @brief 
 * @param ms 
 */
void delay_ms(uint32_t ms)
{
    uint32_t start_time=GetRunTime_ms();
    while(GetRunTime_ms()-start_time<ms)
    {

    }
}
