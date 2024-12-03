/**
 * @file th06.h
 * @author muratdemirtastr@gmail.com
 * @brief th06 i2c temp sensor header file
 *  Created on: Nov 22, 2024
 *      Author: fullstackcoder
 */

#ifndef APPLICATION_BSP_NRF52_BSP_TH06_H_
#define APPLICATION_BSP_NRF52_BSP_TH06_H_

#include "bsp.h"

#define TH06_I2C_DEV_ID                (0x40U >> 1)
#define TH06_HUMI_HOLD_MASTER_MODE     0xE5
#define TH06_HUMI_NO_HOLD_MASTER_MODE  0xF5
#define TH06_TEMP_HOLD_MASTER_MODE     0xE3
#define TH06_TEMP_NO_HOLD_MASTER_MODE  0xF3
#define TH06_RESET                     0xFE
#define TH06_WR_RH                     0xE6
#define TH06_RD_RH                     0xE7
#define TH06_RTV_FROM_PRM              0xE0

extern bool BSP_TH06_ReadHumidity(float* data);
extern bool BSP_TH06_ReadTemperature(float* data);
#endif /* APPLICATION_BSP_NRF52_BSP_TH06_H_ */
