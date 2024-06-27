/**
 * @file: sht31.c
 * @Created on: 10.03.2024
 * @Author: rRaufToprak
 * @Description: SHT31 temperature and humidity sensor source file
 * @Copyright: MIT License
*/

#include "sht31.h"

static uint8_t calculate_crc(const uint8_t *data, size_t length)
{
	uint8_t crc = 0xFF;
	for(size_t i = 0; i < length; i++){
		crc ^= data[i];
		for(size_t j = 0; j < 8; j++){
			if((crc & 0x80u) != 0){
				crc = (uint8_t)((uint8_t)(crc << 1u) ^ 0x31u);
			}else{
				crc <<= 1u;
			}
		}
	}
	return crc;
}
void sht31_init()
{
	sht31_heater_enable(true);
	HAL_Delay(2000);
	sht31_heater_enable(false);
}
void sht31_send_cmd(uint16_t cmd)
{
	uint8_t cmd_buff[2] = {((cmd & 0xFF00)>>8), cmd & 0xFF};
	HAL_I2C_Master_Transmit(&hi2c1, SHT31_I2C_ADDR, cmd_buff, 2, 30);
}

void sht31_heater_enable(bool enable)
{
	if(enable == true)
		sht31_send_cmd(0x306D);
	else
		sht31_send_cmd(0x3066);
}


void sht31_read_data(float *temp, float *hum)
{
	uint8_t buffer[6];

	sht31_send_cmd(SHT31_HIGH_ENABLED_COMMAND);
	HAL_Delay(20);
	
	HAL_I2C_Master_Receive(&hi2c1, SHT31_I2C_ADDR, buffer, 6, 30);
	uint8_t temp_crc = calculate_crc(buffer, 2);
	uint8_t hum_crc = calculate_crc(buffer+3, 2);
	
	if(temp_crc == buffer[2] && hum_crc == buffer[5])
	{
		
	uint16_t temperature_raw = ((uint16_t) buffer[0] << 8) | buffer[1]; 
	uint16_t humidity_raw = ((uint16_t) buffer[3] <<8) | buffer[4];

	*temp = -45.0f + 175.0f * (float)temperature_raw / 65535.0f;
	*hum = 100.0f * (float)humidity_raw / 65535.0f;
	}
}

