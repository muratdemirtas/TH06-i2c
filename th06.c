/**
 * @file th06.c
 * @author muratdemirtastr@gmail.com
 * @brief th06 i2c temp sensor source file
 *  Created on: Nov 22, 2024
 *      Author: fullstackcoder
 */
#include <stdio.h>
#include "th06.h"
#include "nrf_drv_twi.h"
/* TH-06 i2c xfer bufer */
static uint8_t th06_i2c_rx_data[10];
/**
 * TH06 Low level function for i2c xfer
 * @param u8Cmd register addr
 * @return returns true if i2c bus ok
 */
static bool BSP_TH06_I2C_WriteCmd(uint8_t u8Cmd){
	/* xfer params */
    uint8_t i2c_data[2];
    nrf_drv_twi_xfer_desc_t i2c_xfer;
    /* set command */
    i2c_data[0] = u8Cmd;
    /* clear xfer struct */
    memset(&i2c_xfer, 0, sizeof(nrf_drv_twi_xfer_desc_t));
    /* set xfer parameters */
    i2c_xfer.address = TH06_I2C_DEV_ID;
    i2c_xfer.type = NRF_DRV_TWI_XFER_TXRX;
    i2c_xfer.p_primary_buf = (uint8_t*)i2c_data;
    i2c_xfer.primary_length = sizeof(uint8_t);
    i2c_xfer.p_secondary_buf = (uint8_t*)th06_i2c_rx_data;
    i2c_xfer.secondary_length = sizeof(th06_i2c_rx_data);
    return BSP_I2C_Xfer_TX(0, &i2c_xfer);
}
/**
 * TH-06 i2c write read function
 * @param u8Reg register addr
 * @param num read size
 * @param rawdata destination buffer
 * @return returns true if i2c bus is ok
 */
static bool BSP_TH06_I2C_ReadData2byte(uint8_t u8Reg, uint8_t num, uint16_t* rawdata){
	/* clear i2c buffer */
    memset(th06_i2c_rx_data, 0, sizeof(th06_i2c_rx_data));
    /* write command to i2c dev*/
    if(BSP_TH06_I2C_WriteCmd(u8Reg)){
    	/* extract raw data */
    	*rawdata = (th06_i2c_rx_data[num-2] << 8) | (th06_i2c_rx_data[num-1]);
    	return true;
    }else{
    	return false;
    }
}
/**
 * Read Temperature from TH-06
 * @param data destination
 * @return returns true if read success
 */
bool BSP_TH06_ReadTemperature(float* data){
	/* calculation parameters */
	float temp = 0;
	uint16_t rawData = 0;
	/* read from i2c dev */
	if(BSP_TH06_I2C_ReadData2byte(TH06_TEMP_HOLD_MASTER_MODE, 2, &rawData)){
		/* convert float from uint */
		temp = (float)rawData;
		float value = (175.72*temp)/65536;
		*data = value - 46.85;
		return true;
	}else{
		return false;
	}
}
/**
 * Read humidity from TH-06
 * @param data destination
 * @return returns true if read success
 */
bool BSP_TH06_ReadHumidity(float* data){
	/* calculation parameters */
	float humi = 0;
	uint16_t rawData = 0;
	/* read from i2c dev */
	if(BSP_TH06_I2C_ReadData2byte(TH06_HUMI_HOLD_MASTER_MODE, 2, &rawData)){
		/* convert float from uint */
		humi = (float)rawData;
		float value = (125*humi)/65536;
		*data = value - 6;
		return true;
	}else{
		return false;
	}
}
