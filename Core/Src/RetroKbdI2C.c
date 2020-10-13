/*
 * RetroKbdI2C.c
 *
 *  Created on: Oct 13, 2020
 *      Author: tom_h
 *
 *  GitHub: https://github.com/infrapale/RetroKeyPad_I2C_Slave
 */

#include <stdio.h>
#include <string.h>
#include "RetroKbdI2C.h"

static uint8_t  kbd_i2c_addr =  (RKP_I2C_ADDR  << 1);  // Use 8 bit address
static uint32_t kbd_i2c_timeout = HAL_MAX_DELAY;


uint8_t buf[32];
static char status_str[RKP_STATUS_STR_LEN];
I2C_HandleTypeDef *phi2c1;

/**
 * @brief  Initialize I2C Keyboard
 * @param  i2c_handle
 * @param  i2c_addr  7-bit I2C address, not shifted
 * @param  i2c_timeout  milliseconds (32bit)
 * @retval HAL_OK, no verifications currently
 */

HAL_StatusTypeDef kbd_i2c_init(I2C_HandleTypeDef *p_hi2c1, uint8_t i2c_addr, uint32_t i2c_timeout)
{
	phi2c1 = p_hi2c1;
	kbd_i2c_addr = (i2c_addr << 1);
	kbd_i2c_timeout = i2c_timeout;
	return HAL_OK;
}


/**
 * @brief  Read I2C Keyboardr
 * @param  pointer to key
 * @retval HAL Status
 */

HAL_StatusTypeDef kbd_i2c_rd_key(uint8_t *key){
	uint8_t             buf[4];
	HAL_StatusTypeDef   ret;


	*key = 0x00;
	status_str[0] = '\0';
    buf[0] = RKP_REG_KEY_PRESSED ;

    ret = HAL_I2C_Master_Transmit(phi2c1, kbd_i2c_addr, buf, 1, kbd_i2c_timeout);
    if (ret != HAL_OK ){
    	strcpy(status_str, "Keypad Tx: ");
   	}
    else
   	{
    	ret = HAL_I2C_Master_Receive(phi2c1, kbd_i2c_addr, buf, 1, kbd_i2c_timeout);
       	if (ret != HAL_OK )
       	{
       		strcpy(status_str,"Retro keypad Rx : ");
       	}
       	else
       	{
            *key = buf[0];
       	}
    }
   	switch(ret){
    	case HAL_OK:
    		break;
    	case HAL_ERROR:
    		strncat(status_str,"HAL_ERROR", RKP_STATUS_STR_LEN - strlen(status_str) );
    		break;
    	case HAL_BUSY:
    		strncat(status_str,"HAL_BUSY", RKP_STATUS_STR_LEN - strlen(status_str) );
    		break;
    	case HAL_TIMEOUT:
    		strncat(status_str,"HAL_TIMEOUT", RKP_STATUS_STR_LEN - strlen(status_str) );
    		break;
  	}
  	return ret;

}
/**
 * @brief  Read keyboard and get value string
 * @param  temp_str  storage of return string
 * @param  max_len  of temp_string
 * @param  i2c_timeout  milliseconds (32bit)
 * @retval HAL_OK, no verifications currently
 */

HAL_StatusTypeDef kbd_i2c_get_str( char *temp_str, uint16_t max_len){
	HAL_StatusTypeDef   ret;
	uint8_t key;
	ret = kbd_i2c_rd_key( &key);

	if ( max_len >= RKP_STATUS_STR_LEN )
	{
		if (ret == HAL_OK)
		{
			sprintf(temp_str, "Key=%c", key);
		}
		else
		{
			strcpy(temp_str, status_str);
		}
	}
	else
	{
		ret = HAL_ERROR;
		if (max_len >= 16)
		{
			strcpy(temp_str,"Too short!!");
		}
	}
	return ret;

}



