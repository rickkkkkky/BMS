/**
 * @brief: MODBUS从机实例初始化以及寄存器映射
 * @details:
 * @encoding: UTF-8
 * @date: 2024-08-02
 * @author: 刘禹材
 * @version: 1.0
 */

#include <string.h>
#include "RS485_instance.h"
#include "agile_modbus.h"
#include "agile_modbus_slave_util.h"
#include "main.h"
#include "utils.h"
/**
 * @brief 输入寄存器表，包含10个初始值
 *
 * 该数组用于存储Modbus从机的输入寄存器值。
 */
uint16_t _tab_input_registers[150] = {0, 1, 2, 3, 4, 9, 8, 7, 6, 5};

/**
 * @brief 获取输入寄存器映射缓冲区的静态函数
 *
 * 该函数将_tab_input_registers数组的内容复制到提供的缓冲区中。
 *
 * @param buf 目标缓冲区指针
 * @param bufsz 缓冲区大小（字节）
 * @return int 始终返回0，表示操作成功
 */
static int get_input_map_buf(void *buf, int bufsz)
{
    uint16_t *ptr = (uint16_t *)buf;
    for (int i = 0; i < sizeof(_tab_input_registers) /
                            sizeof(_tab_input_registers[0]);
         i++)
    {
        ptr[i] = _tab_input_registers[i];
    }
    return 0;
}

/**
 * @brief 输入寄存器映射表
 *
 * 该数组定义了Modbus从机的输入寄存器映射，包括起始地址、数量和获取函数。
 */
const agile_modbus_slave_util_map_t input_register_maps[1] =
    {
        {0x64, 0xFA, get_input_map_buf, NULL}};

/**
 * @brief 保持寄存器表，包含10个初始值
 *
 * 该数组用于存储Modbus从机的保持寄存器值。
 */
uint16_t _tab_registers[150] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

/**
 * @brief 获取保持寄存器映射缓冲区的静态函数
 *
 * 该函数将_tab_registers数组的内容复制到提供的缓冲区中。
 *
 * @param buf 目标缓冲区指针
 * @param bufsz 缓冲区大小（字节）
 * @return int 始终返回0，表示操作成功
 */
static int get_map_buf(void *buf, int bufsz)
{
    uint16_t *ptr = (uint16_t *)buf;

    for (int i = 0; i < sizeof(_tab_registers) /
                            sizeof(_tab_registers[0]);
         i++)
    {
        ptr[i] = _tab_registers[i];
    }

    return 0;
}

/**
 * @brief 设置保持寄存器映射缓冲区的静态函数
 *
 * 该函数将提供的缓冲区内容复制到_tab_registers数组中。
 *
 * @param index 起始索引
 * @param len 要复制的元素数量
 * @param buf 源缓冲区指针
 * @param bufsz 缓冲区大小（字节）
 * @return int 始终返回0，表示操作成功
 */
static int set_map_buf(int index, int len, void *buf, int bufsz)
{
    uint16_t *ptr = (uint16_t *)buf;
    for (int i = 0; i < len; i++)
    {
        _tab_registers[index + i] = ptr[index + i];
    }

    return 0;
}
uint16_t _tab_argv_registers[150] = {2000, 1, 2, 3, 4, 5, 6, 7, 8, 9};
static int get_map_argv_buf(void *buf, int bufsz)
{
    uint16_t *ptr = (uint16_t *)buf;

    for (int i = 0; i <   sizeof(_tab_argv_registers) 
                         /sizeof(_tab_argv_registers[0]);i++) 
    {
        ptr[i] = _tab_registers[i];
    }

    return 0;
}
static int set_map_argv_buf(int index, int len, void *buf, int bufsz)
{
    uint16_t *ptr = (uint16_t *)buf;
    for (int i = 0; i < len; i++)
    {
        _tab_argv_registers[index + i] = ptr[index + i];
    }
    return 0;
}
/**
 * @brief 保持寄存器映射表
 *
 * 该数组定义了Modbus从机的保持寄存器映射，包括起始地址、数量、获取函数和设置函数。
 */
const agile_modbus_slave_util_map_t register_maps[1] =
    {
        {0x64, 0xFA, get_map_buf, set_map_buf},
        // {0x400, 0x443, get_map_argv_buf, set_map_argv_buf}
        };

const agile_modbus_slave_util_t slave_util =
    {
        .tab_bits=NULL,
        0,
        NULL,
        0,
        register_maps,
        sizeof(register_maps) / sizeof(register_maps[0]),
        input_register_maps,
        sizeof(input_register_maps) / sizeof(input_register_maps[0]),
        NULL,
        NULL,
        NULL};

static uint8_t ctx_send_buf[AGILE_MODBUS_MAX_ADU_LENGTH];
static uint8_t ctx_read_buf[AGILE_MODBUS_MAX_ADU_LENGTH];
static int16_t ctx_read_bufsz = 0;
static agile_modbus_rtu_t ctx_rtu;
static agile_modbus_t *ctx = &ctx_rtu._ctx;
void RS485_Init(void)
{
    usart2_init();
    // PA1  is 485RE
    rcu_periph_clock_enable(RCU_GPIOA);
    GPIO_CTL0(GPIOA) &= ~(0xF << 4);
    GPIO_CTL0(GPIOA) |= (0x01 << 4);
    // gpio_bit_write(RS485_RE_GPIO_Port, RS485_RE_Pin, RESET);
    gpio_bit_write(RS485_RE_GPIO_Port, RS485_RE_Pin, SET);
    agile_modbus_rtu_init(&ctx_rtu, ctx_send_buf, sizeof(ctx_send_buf),
                          ctx_read_buf, sizeof(ctx_read_buf));
    agile_modbus_set_slave(ctx, 1);
}

void RS485_DataCopy(uint8_t *data, uint16_t len)
{
    ctx_read_bufsz = len;
    memcpy(ctx_read_buf, data, len);
}

void RS485_RespondTask(void)
{
    int16_t ctx_send_bufsz = 0;
    if (ctx_read_bufsz > 0)
    {
        ctx_send_bufsz = agile_modbus_slave_handle(ctx, ctx_read_bufsz, 0,
                                                   agile_modbus_slave_util_callback,
                                                   &slave_util, NULL);
        if (ctx_send_bufsz > 0)
        {
            // gpio_bit_write(RS485_RE_GPIO_Port, RS485_RE_Pin, SET);
            gpio_bit_write(RS485_RE_GPIO_Port, RS485_RE_Pin, RESET);
            // usart_transmit_buffer(USART2, ctx->send_buf, ctx_send_bufsz);
            usart_transmit_buffer(UART3, ctx->send_buf, ctx_send_bufsz);
            // gpio_bit_write(RS485_RE_GPIO_Port, RS485_RE_Pin, RESET);
            gpio_bit_write(RS485_RE_GPIO_Port, RS485_RE_Pin, SET);
            // _tab_registers[0]++;
            ctx_read_bufsz = 0;
            // memset(ctx_read_buf, 0, sizeof(ctx_read_buf));
        }
    }
}
