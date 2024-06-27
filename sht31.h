/**
 * @file: sht31.h
 * @Created on: 10.03.2024
 * @Author: rRaufToprak
 * @Description: SHT31 temperature and humidity sensor header file
 * @Copyright: MIT License
*/

#ifndef _SHT31_H_
#define _SHT31_H_

#include "stdint.h"
#include "stdbool.h"
#include "stm32f4xx_hal.h"
#include "i2c.h"

#define SHT31_I2C_ADDR 																	0x44<<1

/*------------------SHT31 Commands--------------------------*/
#define SHT31_HIGH_ENABLED_COMMAND											0x2C06
#define SHT31_MEDIUM_ENABLED_COMMAND										0x2C0D
#define SHT31_LOW_ENABLED_COMMAND												0x2C10
#define SHT31_HIGH_DISABLED_COMMAND											0x2400
#define SHT31_MEDIUM_DISABLED_COMMAND										0x240B
#define SHT31_LOW_DISABLED_COMMAND											0x2416
#define SHT31_BREAK_COMMAND															0x3093
#define SHT31_SOFT_RESET_COMMAND												0x30A2
#define SHT31_HEATER_ENABLE_COMMAND											0x306D
#define SHT31_HEATER_DISABLE_COMMAND										0x3066
#define SHT31_READ_STATUS_REGISTER_COMMAND							0xF32D
#define SHT31_CLEAR_STATUS_REGISTER_COMMAND							0x3041



/**
 *Initialize the SHT31
 */
void sht31_init(void);
/**
 *Enable the sensor heater.
 *@param true for enable and false for disabled
 */
void sht31_heater_enable(bool enable);
/**
 *Sends commands to SHT31
 *@param 16 bit command
 */
void sht31_send_cmd(uint16_t cmd);
/**
 *Temperature and humidity read function.
 *@param Address of temperature variable
 *@param Address of humidity variable
 */
void sht31_read_data(float *temp, float *hum);

#endif /*	_SHT31_H_	*/



