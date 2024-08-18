 /**
 * @note: Compiler: AC5 with -O3 optimization
 * @note: Standard: C99 tab-width: 4
 * @brief: 定时器配置
 * @details: TIM5   1ms基本定时器  
 * @encoding: UTF-8
 * @date: 2024-07-23
 * @author: 刘禹材
 * @version: 1.0
 */

#include "main.h"
/**
 * @brief: 初始化定时器5 1ms
 */
void TIM5_Init(void)
{
    timer_parameter_struct timer_initpara;
    
    rcu_periph_clock_enable(RCU_TIMER5);
    timer_deinit(TIMER5);
    
    timer_initpara.prescaler         = (120 - 1);
    timer_initpara.alignedmode       = TIMER_COUNTER_EDGE;
    timer_initpara.counterdirection  = TIMER_COUNTER_UP;
    timer_initpara.period            = (1000 - 1);
    timer_initpara.clockdivision     = TIMER_CKDIV_DIV1;
    timer_init(TIMER5, &timer_initpara);
    
    
    timer_interrupt_flag_clear(TIMER5, TIMER_INT_FLAG_UP);
    timer_interrupt_enable(TIMER5, TIMER_INT_UP);
    timer_enable(TIMER5);
    
}

 
 

