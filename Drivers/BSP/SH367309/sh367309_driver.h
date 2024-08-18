#ifndef SH367309_DRIVER_H
#define SH367309_DRIVER_H
#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
// EEPROM寄存器列表
#define SH367309_REG_SCONF1                 0x00
#define SH367309_REG_SCONF2                 0x01
#define SH367309_REG_OVT_LDRT_OVH           0x02
#define SH367309_REG_OVL                    0x03
#define SH367309_REG_UVT_OVRH               0x04
#define SH367309_REG_OVRL                   0x05
#define SH367309_REG_UV                     0x06
#define SH367309_REG_UVR                    0x07
#define SH367309_REG_BALV                   0x08
#define SH367309_REG_PREV                   0x09
#define SH367309_REG_L0V                    0x0A
#define SH367309_REG_PFV                    0x0B
#define SH367309_REG_OCD1V_OCD1T            0x0C
#define SH367309_REG_OCD2V_OCD2T            0x0D
#define SH367309_REG_SCV_SCT                0x0E
#define SH367309_REG_OCCV_OCCT              0x0F
#define SH367309_REG_MOST_OCRT_PFT          0x10
#define SH367309_REG_OTC                    0x11
#define SH367309_REG_OTCR                   0x12
#define SH367309_REG_UTC                    0x13
#define SH367309_REG_UTCR                   0x14
#define SH367309_REG_OTD                    0x15
#define SH367309_REG_OTDR                   0x16
#define SH367309_REG_UTD                    0x17
#define SH367309_REG_UTDR                   0x18
#define SH367309_REG_TR                     0x19
//RAM寄存器列表(掉电丢失)
#define SH367309_RAM_CONF                   0x40
#define SH367309_RAM_BALANCEH               0x41
#define SH367309_RAM_BALANCEL               0x42
#define SH367309_RAM_BSTATUS1               0x43
#define SH367309_RAM_BSTATUS2               0x44
#define SH367309_RAM_BSTATUS3               0x45
#define SH367309_RAM_TEMP1H                 0x46
#define SH367309_RAM_TEMP1L                 0x47
#define SH367309_RAM_TEMP2H                 0x48
#define SH367309_RAM_TEMP2L                 0x49
#define SH367309_RAM_TEMP3H                 0x4A
#define SH367309_RAM_TEMP3L                 0x4B
#define SH367309_RAM_CURH                   0x4C
#define SH367309_RAM_CURL                   0x4D
#define SH367309_RAM_CELL1H                 0x4E
#define SH367309_RAM_CELL1L                 0x4F
#define SH367309_RAM_CELL2H                 0x50
#define SH367309_RAM_CELL2L                 0x51
#define SH367309_RAM_CELL3H                 0x52
#define SH367309_RAM_CELL3L                 0x53
#define SH367309_RAM_CELL4H                 0x54
#define SH367309_RAM_CELL4L                 0x55
#define SH367309_RAM_CELL5H                 0x56
#define SH367309_RAM_CELL5L                 0x57
#define SH367309_RAM_CELL6H                 0x58
#define SH367309_RAM_CELL6L                 0x59
#define SH367309_RAM_CELL7H                 0x5A
#define SH367309_RAM_CELL7L                 0x5B
#define SH367309_RAM_CELL8H                 0x5C
#define SH367309_RAM_CELL8L                 0x5D
#define SH367309_RAM_CELL9H                 0x5E
#define SH367309_RAM_CELL9L                 0x5F
#define SH367309_RAM_CELL10H                0x60
#define SH367309_RAM_CELL10L                0x61
#define SH367309_RAM_CELL11H                0x62
#define SH367309_RAM_CELL11L                0x63
#define SH367309_RAM_CELL12H                0x64
#define SH367309_RAM_CELL12L                0x65
#define SH367309_RAM_CELL13H                0x66
#define SH367309_RAM_CELL13L                0x67
#define SH367309_RAM_CELL14H                0x68
#define SH367309_RAM_CELL14L                0x69
#define SH367309_RAM_CELL15H                0x6A
#define SH367309_RAM_CELL15L                0x6B
#define SH367309_RAM_CELL16H                0x6C
#define SH367309_RAM_CELL16L                0x6D
#define SH367309_RAM_CADCDH                 0x6E
#define SH367309_RAM_CADCDL                 0x6F
#define SH367309_RAM_BFLAG1                 0x70
#define SH367309_RAM_BFLAG2                 0x71
#define SH367309_RAM_RSTSTAT                0x72

typedef struct 
{
    uint8_t iic_addr;                                                                              
    uint8_t (*iic_init)(void);                                                                     
    uint8_t (*iic_deinit)(void);                                                                   
    uint8_t (*iic_read)(uint8_t addr, uint8_t reg, uint8_t *buf, uint16_t len);                    
    uint8_t (*iic_write)(uint8_t addr, uint8_t reg, uint8_t *buf, uint16_t len);                       
    void (*delay_ms)(uint32_t ms);                                                         
    void (*debug_print)(const char *const fmt, ...);                                                                                                                                
    uint8_t inited;

}sh367309_handle_t;

// SH367309支持四种工作模式：保护模式、采集模式、仓运模式、烧写模式。
typedef enum
{
    SH367309_MODE_PROTECT = 0,
    SH367309_MODE_COLLECT,
    SH367309_MODE_DELIVERY,
    SH367309_MODE_WRITE
}sh367309_mode_t;
}

#ifdef __cplusplus
}
#endif
#endif // SH367309_DRIVER_H
