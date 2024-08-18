/**
* @brief:
* @details: 每个十进制数字用4位二进制数表示。在表示时间时，通常将小时、分钟和秒分别用BCD码表示。
           以下是一个用BCD码表示时间的示例：
           假设当前时间是 12:34:56，我们可以将其表示为：
           小时：12 -> 0001 0010
           分钟：34 -> 0011 0100
           秒：56 -> 0101 0110
* @encoding: UTF-8
* @date: 2024-08-02
* @author: 刘禹材
* @version: 1.0
*/

#include <stddef.h>
#include "BL5372_driver.h"

uint8_t BL5372_Init(bl5372_handle_t *handle)
{
    if (handle == NULL)
    {
        handle->debug_print("BL5372 handle is NULL\r\n");
        return 1;
    }
    if (  handle->debug_print == NULL || handle->iic_read   == NULL || handle->iic_write == NULL
        ||handle->iic_init    == NULL || handle->iic_deinit == NULL)
    {
        handle->debug_print("BL5372 handle is not complete\r\n");
    }
    handle->iic_init();
    handle->inited = 1;
    return 0;
}
/**
 * @brief  将十进制数字转换为BCD码
 * @details
 * @param decimal_num
 * @return
 */
static uint8_t decimal_to_bcd(uint8_t decimal_num)
{
    uint8_t bcd_num = 0;
    uint8_t shift = 0;

    while (decimal_num > 0)
    {

        uint8_t digit = decimal_num % 10;

        bcd_num |= (digit << (shift * 4));

        decimal_num /= 10;

        shift++;
    }

    return bcd_num;
}
/**
 * @brief  将BCD码转换为十进制数字
 * @param bcd_num
 * @return
 */
static uint8_t bcd_to_decimal(uint8_t bcd_num)
{
    uint8_t decimal_num = 0;
    uint8_t multiplier = 1;

    while (bcd_num > 0)
    {

        uint8_t digit = bcd_num & 0x0F;

        decimal_num += digit * multiplier;

        bcd_num >>= 4;

        multiplier *= 10;
    }

    return decimal_num;
}

/**
 * @brief 获取当前时间
 * @note len 1  2  3  4   5  6  7
 *       buf 秒 分 时 星期 日 月 年
 * @param handle
 * @param buf
 * @param len
 * @return
 */
uint8_t BL5372_get_RTC(bl5372_handle_t *handle, uint8_t *buf, uint8_t len)
{
    len = (len > 7) ? 7 : len;
    handle->iic_read(handle->iic_addr, BL5372_REG_SECOND << 4, buf, len);
    for (uint8_t i = 0; i < len; i++)
    {
        buf[i] = bcd_to_decimal(buf[i]);
    }
    return 0;
}
/**
 * @brief  设置当前时间
 * @param handle
 * @param buf
 * @param len
 * @return
 */
uint8_t BL5372_set_RTC(bl5372_handle_t *handle, uint8_t *buf, uint8_t len)
{
    len = (len > 7) ? 7 : len;
    for (uint8_t i = 0; i < len; i++)
    {
        buf[i] = decimal_to_bcd(buf[i]);
    }
    handle->iic_write(handle->iic_addr, BL5372_REG_SECOND << 4, buf, len);
    return 0;
}