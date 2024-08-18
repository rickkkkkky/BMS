 /**
 * @note: Compiler: AC5 with -O3 optimization
 * @note: Standard: C99 tab-width: 4
 * @brief: 使用IO口模拟IIC
 * @details: 
 * @encoding: UTF-8
 * @date: 2024-08-3
 * @author: 刘禹材
 * @version 1.11
 */
#include "iic_interface.h"

#ifdef IIC_DEBUG_ENABLED
    #include "utils.h"
    #define IIC_ERROR_PRINTF(format, ...) UART_Printf(UART3, "IIC error: " format, ##__VA_ARGS__)
#else
    #define IIC_ERROR_PRINTF(format, ...) \
        do                                \
        {                                 \
                                          \
        } while (0)
#endif

#define GPIO_PIN_SET   1
#define GPIO_PIN_RESET 0
#define NULL           0

static void IICStart(iic_bus *bus)
{
    bus->GPIO_WritePin(bus->GPIOx_SDA, bus->GPIO_SDA_Pin, GPIO_PIN_SET);
    bus->GPIO_WritePin(bus->GPIOx_SCL, bus->GPIO_SCL_Pin, GPIO_PIN_SET);
    bus->delay_us(bus->delay_start_condition);

    bus->GPIO_WritePin(bus->GPIOx_SDA, bus->GPIO_SDA_Pin, GPIO_PIN_RESET);
    bus->delay_us(bus->delay_after_sda_change);

    bus->GPIO_WritePin(bus->GPIOx_SCL, bus->GPIO_SCL_Pin, GPIO_PIN_RESET);
    bus->delay_us(bus->delay_start_condition);
}

// IIC 总线停止条件
static void IICStop(iic_bus *bus)
{
    bus->GPIO_WritePin(bus->GPIOx_SDA, bus->GPIO_SDA_Pin, GPIO_PIN_RESET);
    bus->delay_us(bus->delay_after_sda_change);

    bus->GPIO_WritePin(bus->GPIOx_SCL, bus->GPIO_SCL_Pin, GPIO_PIN_SET);
    bus->delay_us(bus->delay_start_condition);

    bus->GPIO_WritePin(bus->GPIOx_SDA, bus->GPIO_SDA_Pin, GPIO_PIN_SET);
    bus->delay_us(bus->delay_after_sda_change);

}

/**
 * @brief 等待应答
 * @param bus IIC总线结构体指针
 * @return uint8_t 返回应答状态，0表示有应答，1表示无应答
 */
static uint8_t IICWaitAck(iic_bus *bus)
{
    uint8_t ack=0;
    uint8_t waittime=0;
    uint8_t temp;
    bus->GPIO_WritePin(bus->GPIOx_SDA, bus->GPIO_SDA_Pin, GPIO_PIN_SET);
    bus->delay_us(bus->delay_after_sda_change);

    bus->GPIO_WritePin(bus->GPIOx_SCL, bus->GPIO_SCL_Pin, GPIO_PIN_SET);
    bus->delay_us(bus->delay_start_condition);
    
    do
    {
        temp=(bus->GPIO_ReadPin(bus->GPIOx_SDA, bus->GPIO_SDA_Pin));
        waittime++;
        if(waittime>250)
        {
            IICStop(bus);
            ack=1;
            break;
        }
    } while (temp);

    bus->GPIO_WritePin(bus->GPIOx_SCL, bus->GPIO_SCL_Pin, GPIO_PIN_RESET);
    bus->delay_us(bus->delay_start_condition);
    return ack ;
}

// 发送 ACK
static void IICSendAck(iic_bus *bus)
{
    bus->GPIO_WritePin(bus->GPIOx_SDA, bus->GPIO_SDA_Pin, GPIO_PIN_RESET);
    bus->delay_us(bus->delay_after_sda_change);

    bus->GPIO_WritePin(bus->GPIOx_SCL, bus->GPIO_SCL_Pin, GPIO_PIN_SET);
    bus->delay_us(bus->delay_start_condition);

    bus->GPIO_WritePin(bus->GPIOx_SCL, bus->GPIO_SCL_Pin, GPIO_PIN_RESET);
    bus->delay_us(bus->delay_start_condition);

    bus->GPIO_WritePin(bus->GPIOx_SDA, bus->GPIO_SDA_Pin, GPIO_PIN_SET);
    bus->delay_us(bus->delay_after_sda_change);
}

// 发送 Not ACK
static void IICSendNotAck(iic_bus *bus)
{
    bus->GPIO_WritePin(bus->GPIOx_SDA, bus->GPIO_SDA_Pin, GPIO_PIN_SET);
    bus->delay_us(bus->delay_after_sda_change);

    bus->GPIO_WritePin(bus->GPIOx_SCL, bus->GPIO_SCL_Pin, GPIO_PIN_SET);
    bus->delay_us(bus->delay_start_condition);

    bus->GPIO_WritePin(bus->GPIOx_SCL, bus->GPIO_SCL_Pin, GPIO_PIN_RESET);
    bus->delay_us(bus->delay_start_condition);
}

// 发送一个字节
static void IICSendByte(iic_bus *bus, uint8_t byte)
{
    for (uint8_t i = 0; i < 8; i++)
    {
        bus->GPIO_WritePin(bus->GPIOx_SDA, bus->GPIO_SDA_Pin, ((byte & 0x80)>>7));
        byte <<= 1;
        bus->delay_us(bus->delay_after_sda_change);

        bus->GPIO_WritePin(bus->GPIOx_SCL, bus->GPIO_SCL_Pin, GPIO_PIN_SET);
        bus->delay_us(bus->delay_start_condition);

        bus->GPIO_WritePin(bus->GPIOx_SCL, bus->GPIO_SCL_Pin, GPIO_PIN_RESET);
    }
    bus->GPIO_WritePin(bus->GPIOx_SDA, bus->GPIO_SDA_Pin, GPIO_PIN_SET);
}

// 接收一个字节
static uint8_t IICReceiveByte(iic_bus *bus, uint8_t ack)
{
    uint8_t byte = 0;
    bus->GPIO_WritePin(bus->GPIOx_SDA, bus->GPIO_SDA_Pin, GPIO_PIN_SET);

    for (uint8_t i = 0; i < 8; i++)
    {
        byte <<= 1;
        bus->GPIO_WritePin(bus->GPIOx_SCL, bus->GPIO_SCL_Pin, GPIO_PIN_SET);
        bus->delay_us(bus->delay_start_condition);

        if (bus->GPIO_ReadPin(bus->GPIOx_SDA, bus->GPIO_SDA_Pin))
        {
            byte++;
        }
        bus->GPIO_WritePin(bus->GPIOx_SCL, bus->GPIO_SCL_Pin, GPIO_PIN_RESET);
        bus->delay_us(bus->delay_start_condition);
    }

    if (ack)
    {
        IICSendAck(bus);
    }
    else
    {
        IICSendNotAck(bus);
    }
    return byte;
}

// 初始化 IIC 总线
// uint8_t IICInit(iic_bus *bus)
// {
//     if( bus->delay_us      == NULL || bus->GPIO_Init    == NULL || bus->GPIO_DeInit == NULL || 
//         bus->GPIO_WritePin == NULL || bus->GPIO_ReadPin == NULL                               )
//     {
//         return 1;
//     }
//     else
//     {
//         bus->inited=1;
//         return 0;
//     }
// }

// 写一个字节
uint8_t IIC_Write_One_Byte(iic_bus *bus, uint8_t addr, uint8_t reg, uint8_t data)
{
    IICStart(bus);
    IICSendByte(bus, addr);
    if (IICWaitAck(bus))
    {
        IICStop(bus);
        IIC_ERROR_PRINTF("device no ack!\n");
        return 1;
    }
    IICSendByte(bus, reg);
    IICWaitAck(bus);
    IICSendByte(bus, data);
    IICWaitAck(bus);
    IICStop(bus);
    return 0;
}


uint8_t IIC_Write_Multi_Byte(iic_bus *bus, uint8_t addr, uint8_t reg, uint8_t *data, uint16_t length)
{
    IICStart(bus);
    IICSendByte(bus, addr);
    if (IICWaitAck(bus))
    {
        IICStop(bus);
        IIC_ERROR_PRINTF("device no ack!\n");
        return 1;
    }
    IICSendByte(bus, reg);
    if (IICWaitAck(bus))
    {
        IICStop(bus);
        IIC_ERROR_PRINTF("device no ack!\n");
        return 1;
    }
    for (uint16_t i = 0; i < length; i++)
    {
        IICSendByte(bus, data[i]);
        if (IICWaitAck(bus))
        {
            IICStop(bus);
            IIC_ERROR_PRINTF("device no ack!\n");
            return 1;
        }
    }
    IICStop(bus);
    return 0;
}

// 读一个字节
uint8_t IIC_Read_One_Byte(iic_bus *bus, uint8_t addr, uint8_t reg)
{
    uint8_t data;

    IICStart(bus);
    IICSendByte(bus, addr);
    if (IICWaitAck(bus))
    {
        IICStop(bus);
        IIC_ERROR_PRINTF("device addr no ack!\n");
        return 1;
    }
    IICSendByte(bus, reg);
    if (IICWaitAck(bus))
    {
        IICStop(bus);
        IIC_ERROR_PRINTF("device reg no ack!\n");
        return 1;
    }
    IICStart(bus);
    IICSendByte(bus, addr | 0x01);
    if (IICWaitAck(bus))
    {
        IICStop(bus);
        IIC_ERROR_PRINTF("device read byte no ack!\n");
        return 1;
    }
    data = IICReceiveByte(bus, 0);
    IICStop(bus);

    return data;
}

// 读多个字节
uint8_t IIC_Read_Multi_Byte(iic_bus *bus, uint8_t addr, uint8_t reg, uint8_t *data, uint16_t length)
{
    IICStart(bus);
    IICSendByte(bus, addr);
    if (IICWaitAck(bus))
    {
        IICStop(bus);
        IIC_ERROR_PRINTF("device addr no ack!\n");
        return 1;
    }
    IICSendByte(bus, reg);
    if (IICWaitAck(bus))
    {
        IICStop(bus);
        IIC_ERROR_PRINTF("device reg no ack!\n");
        return 1;
    }
    IICStart(bus);
    IICSendByte(bus, addr | 0x01);
    if (IICWaitAck(bus))
    {
        IICStop(bus);
        IIC_ERROR_PRINTF("device read buf no ack!\n");
        return 1;
    }
    for (uint16_t i = 0; i < length; i++)
    {
        data[i] = IICReceiveByte(bus, (i == (length - 1)) ? 0 : 1);
    }
    IICStop(bus);

    return 0;
}
uint8_t IIC_check_device(iic_bus *bus,uint8_t addr)
{
    IICStart(bus);
    IICSendByte(bus, addr);
    if (IICWaitAck(bus))
    {
        IICStop(bus);
        IIC_ERROR_PRINTF("device addr no ack!\n");
        return 1;
    }
    IICStop(bus);
    return 0;

}
uint8_t IIC_Write_Multi_Byte_16Reg_Addr( iic_bus *bus, uint8_t addr, uint16_t reg,
                                         uint8_t *data, uint16_t length)
{
    IICStart(bus);
    IICSendByte(bus, addr);
    if (IICWaitAck(bus))
    {
        IICStop(bus);
        IIC_ERROR_PRINTF("device addr no ack!\n");
        return 1;
    }
    IICSendByte(bus, reg >> 8);
    if (IICWaitAck(bus))
    {
        IICStop(bus);
        IIC_ERROR_PRINTF("device reg no ack!\n");
        return 1;
    }
    IICSendByte(bus, reg & 0xff);
    if (IICWaitAck(bus))
    {
        IICStop(bus);
        IIC_ERROR_PRINTF("device reg no ack!\n");
        return 1;
    }
    // IICStart(bus);
    // IICSendByte(bus, addr );
    // if (IICWaitAck(bus))
    // {
    //     IICStop(bus);
    //     IIC_ERROR_PRINTF("device read buf no ack!\n");
    //     return 1;
    // }
    for (uint16_t i = 0; i < length; i++)
    {
        IICSendByte(bus, data[i]);
        if (IICWaitAck(bus))
        {
            IICStop(bus);
            IIC_ERROR_PRINTF("device no ack!\n");
            return 1;
        }
    }
    IICStop(bus);
    return 0;
}
uint8_t IIC_Read_Multi_Byte_16Reg_Addr( iic_bus *bus, uint8_t addr, uint16_t reg,   
                                        uint8_t *data, uint16_t length)
{
    IICStart(bus);
    IICSendByte(bus, addr);
    if (IICWaitAck(bus))
    {
        IICStop(bus);
        IIC_ERROR_PRINTF("device addr no ack!\n");
        return 1;
    }
    IICSendByte(bus, reg >> 8);
    if (IICWaitAck(bus))
    {
        IICStop(bus);
        IIC_ERROR_PRINTF("device H reg no ack!\n");
        return 1;
    }
    IICSendByte(bus, reg & 0xff);
    if (IICWaitAck(bus))
    {
        IICStop(bus);
        IIC_ERROR_PRINTF("device L reg no ack!\n");
        return 1;
    }
    IICStart(bus);
    IICSendByte(bus, addr | 0x01);
    if (IICWaitAck(bus))
    {
        IICStop(bus);
        IIC_ERROR_PRINTF("device read buf no ack!\n");
        return 1;
    }
    for (uint16_t i = 0; i < length; i++)
    {
        data[i] = IICReceiveByte(bus, (i == (length - 1)) ? 0 : 1);
    }
    IICStop(bus);

    return 0;
}



