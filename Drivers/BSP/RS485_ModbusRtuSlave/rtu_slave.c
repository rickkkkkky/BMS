#include "slave.h"
#include <stdio.h>
#include <stdlib.h>
#include "main.h"

uint8_t ctx_send_buf[AGILE_MODBUS_MAX_ADU_LENGTH];
uint8_t ctx_read_buf[AGILE_MODBUS_MAX_ADU_LENGTH];
// uint8_t ctx_test_buf[]= {0X01,0X03,0X00,0X00,0X00,0X0A,0XC5,0XCD};
int16_t ctx_read_bufsz=0;
int16_t ctx_send_bufsz=0;
void *rtu_entry(void *param)
{


    agile_modbus_rtu_t ctx_rtu;
    agile_modbus_t *ctx = &ctx_rtu._ctx;
    agile_modbus_rtu_init(&ctx_rtu, ctx_send_buf, sizeof(ctx_send_buf), ctx_read_buf, sizeof(ctx_read_buf));
    // agile_modbus_rtu_init(&ctx_rtu, ctx_send_buf, sizeof(ctx_send_buf), ctx_test_buf, sizeof(ctx_test_buf));
    agile_modbus_set_slave(ctx, 1);

    // LOG_I("Running.");

    while (1) {
        // int read_len = serial_receive(_fd, ctx->read_buf, ctx->read_bufsz, 1000);
        // if (read_len < 0) {
        //     // LOG_E("Receive error, now exit.");
        //     break;
        // }

        if (ctx_read_bufsz == 0)
            continue;

        ctx_send_bufsz = agile_modbus_slave_handle(ctx, ctx_read_bufsz, 0, 
                                                 agile_modbus_slave_util_callback,
                                                  &slave_util, NULL);
        // serial_flush(_fd);
        UART_Printf(&huart1, "send_bufsz:%d\r\n",ctx_send_bufsz);
        if (ctx_send_bufsz > 0)
        {
            HAL_GPIO_WritePin(RS485_RE_GPIO_Port,RS485_RE_Pin,GPIO_PIN_SET);
            HAL_UART_Transmit(&huart3, ctx->send_buf, ctx_send_bufsz,1000);
            HAL_GPIO_WritePin(RS485_RE_GPIO_Port,RS485_RE_Pin,GPIO_PIN_RESET);
            _tab_registers[0]++;
            ctx_read_bufsz=0;
            // for(uint16_t i=0;i<ctx_send_bufsz;i++)
            // {
            //     UART_Printf(&huart1, "%02X ",ctx->send_buf[i]);
            // }
            // UART_Printf(&huart1, "\r\n");
        }
        

        // break;
    }

    // serial_close(_fd, &_old_tios);
}

