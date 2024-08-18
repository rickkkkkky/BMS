/**
 * @note: Compiler: AC5 with -O3 optimization
 * @note: Standard: C99 tab-width: 4
 * @brief: 主函数
 * @details:
 * @encoding: UTF-8
 * @date: 2024-07-23
 * @author: 刘禹材
 * @version: 1.0
 */
#include "main.h"
#include "system_gd32f30x.h"
#include "utils.h"
#include "led_instance.h"
#include "AT24Cxx_instance.h"
#include "BL5372_instance.h"
#include "RS485_instance.h"
static void NVIC_Configuration(void);
static void MCU_Init(void);
static void Peripherals_Init(void);
int main(void)
{
    SystemInit(); // 120MHz clock
    NVIC_Configuration();
    MCU_Init();
    Peripherals_Init();

    // LED_state.breath(&LED_state,2000,5);
    LED_alert.on(&LED_alert);
    LED_soc1.on(&LED_soc1);
    LED_soc2.off(&LED_soc2);
    LED_soc3.on(&LED_soc3);
    LED_soc4.on(&LED_soc4);
    uint32_t last_time = 0;
    uint32_t time;
    uint8_t data[1024];

    // for(uint16_t i=0;i<1024*1;i=i+1024) //8条记录
    // {
    //     UART_Printf(UART3,"\n\r===%d=======\n\r" ,i);
    //     // delay_ms(1000);
    //     at24cxx_basic_read(i,data,sizeof(data));
    //     for(uint16_t j=0;j<1024;j=j+2)
    //     {
    //         if( (j)%10==0 )
    //             UART_Printf( UART3,"\n");
    //         if( (j)%64==0 )
    //             UART_Printf( UART3,"---\n\n----");
    //         UART_Printf(UART3, "%d=%d ", j,((data[j]<<8)+data[j+1]));
    //     }
    // }
    uint8_t buf_temp2[16]={0};
    while (1)
    {
        time = GetRunTime_s();
        RS485_RespondTask();
        if (time - last_time >= 1)
        {
            GPIO_OCTL(GPIOB) ^= (1 << 2);
            // if (gpio_input_bit_get(GPIOB, GPIO_PIN_2))
            //     LED_alert.on(&LED_alert);
            // else
            //     LED_alert.off(&LED_alert);
            // ADC_get_Data();
            // UART_Printf(UART3,"GetRunTime_s=%d\r\n",time);
            // usart_data_transmit(UART3,time);
            // IIC_Read_Multi_Byte(&IIC[1], 0X64, 0, buf_temp2, 16);
            // for (uint16_t i = 0; i < 16; i++)
            // {
            //     UART_Printf(UART3, "%d=[%02X] ", i, buf_temp2[i]);
            // }
            // UART_Printf(UART3, "\r\n");
            last_time = time;
        }
    }
}
/**
 * @brief 越小越高 注释某中断后 中断不会工作
 * @param
 */
void NVIC_Configuration(void)
{
    nvic_irq_enable(USART2_IRQn, 0, 0);
    nvic_irq_enable(UART3_IRQn, 0, 1);
    nvic_irq_enable(TIMER5_IRQn, 0, 1);
}
void MCU_Init(void)
{
    TIM5_Init();
    uart3_init();
    ADC_Init();
}
void Peripherals_Init(void)
{
    /*!< 释放PB3 PB4做普通IO!!! */
    rcu_periph_clock_enable(RCU_AF);
    gpio_pin_remap_config(GPIO_SWJ_SWDPENABLE_REMAP, ENABLE);

    // GPIO_OCTL(GPIOA) = 0x2030;
    // GPIO_CTL0(GPIOA) = 0x10551111;
    // GPIO_CTL1(GPIOA) = 0x18811114;

    // PORT B GROUP
    /*BIT       15     14     13     12     11     10     9     8     7     6     5     4     3     2     1     0   */
    /*OCTL      0      0      1      1      0      0      0     0     0     1     0     0     0     0     0     0   */
    /*MD        1      0      1      1      1      1      0     0     1     1     1     0     1     1     1     1   */
    /*CTL       0      1      1      1      0      0      1     1     0     0     0     1     0     0     0     0   */
    /*NAME	  R_SCP  S_SCP   SCL1   SDA1    -      -    CHC-2  CHC    -    DSG   CHG   REV   PWM   LED1  LED2  LED3 */

    // GPIO_OCTL(GPIOB) = 0x3040;
    // GPIO_CTL0(GPIOB) = 0x11141111;
    // GPIO_CTL1(GPIOB) = 0x14551144;

    // PORT C GROUP
    /*BIT       15     14     13     12     11     10     9     8     7     6     5     4     3     2     1     0   */
    /*OCTL      0      0      0      1      0      0      0     0     0     0     0     0     0     0     0     0   */
    /*MD        0      0      0      1      1      1      0     0     0     0     1     1     0     0     0     0   */
    /*CTL       1      1      1      0      0      0      1     1     1     1     0     0     0     0     0     0   */
    /*NAME	   WAKE    SW     PW     -     RX0    TX0     S1    S2    S3    S4   LED4  LED5   T4    T3    T2    T1  */

    // GPIO_OCTL(GPIOC) = 0x00000000;
    // GPIO_CTL0(GPIOC) = 0x44110000;
    // GPIO_CTL1(GPIOC) = 0x44411144;

    // PORT D GROUP
    /*BIT       15     14     13     12     11     10     9     8     7     6     5     4     3     2     1     0   */
    /*OCTL      0      0      0      0      0      0      0     0     0     0     0     0     0     0     0     0   */
    /*MD        1      1      1      1      1      1      1     1     1     1     1     1     1     1     1     1   */
    /*CTL       0      0      0      0      0      0      0     0     0     0     0     0     0     0     0     0   */
    /*NAME		-      -      -      -      -      -      -     -     -     -     -     -     -      -     -    -   */

    // GPIO_OCTL(GPIOD) = 0x00000000;
    // GPIO_CTL0(GPIOD) = 0x11111111;
    // GPIO_CTL1(GPIOD) = 0x11111111;

    LED_state.init(&LED_state);
    LED_alert.init(&LED_alert);
    LED_soc1.init(&LED_soc1);
    LED_soc2.init(&LED_soc2);
    LED_soc3.init(&LED_soc3);
    LED_soc4.init(&LED_soc4);
    // GPIO_BOP(GPIOB) = GPIO_PIN_3; // 外围设备使能？？
    rcu_periph_clock_enable(RCU_GPIOB);
    GPIO_CTL0(GPIOB) &= ~(0xF << 12);
    GPIO_CTL0(GPIOB) |= (0x01 << 12);
    gpio_bit_write(GPIOB, GPIO_PIN_3, SET);

    at24cxx_basic_init(AT24C512, AT24CXX_ADDRESS_A000);
    bl5372_basic_init();
    RS485_Init();
}
