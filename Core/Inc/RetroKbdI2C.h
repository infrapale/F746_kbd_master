/*
 * RetroKbdI2C.h
 *
 *  Created on: Oct 13, 2020
 *      Author: tom_h
 */

#ifndef INC_RETROKBDI2C_H_
#define INC_RETROKBDI2C_H_

#include "stm32f7xx_hal.h"

#define RKP_I2C_ADDR             0x18
#define RKP_REG_KEYDEF           0x10
#define RKP_REG_KEY_PRESSED      0x20
#define RKP_MAX_DELAY            1000
#define RKP_STATUS_STR_LEN       32

HAL_StatusTypeDef kbd_i2c_init(I2C_HandleTypeDef *p_hi2c1, uint8_t i2c_addr, uint32_t i2c_timeout);
HAL_StatusTypeDef kbd_rd_key(uint8_t *key);
HAL_StatusTypeDef kbd_I2C_get_str( char *temp_str, uint16_t max_len);




#endif /* INC_RETROKBDI2C_H_ */
