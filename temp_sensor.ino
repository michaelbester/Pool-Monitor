/******************************************************************************/
/* Project:     Pool Monitor                                           	      */
/*                                                                            */
/* FileName:    temp_sensor.cpp	                                              */
/*                                                                            */
/* Author:      Michael Bester                                                */
/*                                                                            */
/* Overview:    This module contains temperature sensor code.				  */
/*                                                                            */
/* Notes:                                                                     */
/*                                                                            */
/******************************************************************************/

/***************************** Include Files **********************************/
#include "init.h"
#include "temp_sensor.h"
#include <OneWire.h>

/******************************************************************************/
/* Function:    float Read_Temperature(void)               	                  */
/*                                                                            */
/* Inputs:      None.                                                         */
/*                                                                            */
/* Outputs:     Temperature in F degrees.                                     */
/*                                                                            */
/* Description: This function will read the temperature in F from the Dallas  */
/*				Semiconductor DS18b20 device.								  */
/*                                                                            */
/* Author:      Michael Bester                                                */
/*                                                                            */
/* Notes:		Using digital pin 0 for the one wire interface.			      */
/*                                                                            */
/******************************************************************************/
float Read_Temperature(void)
{
	uint8_t data[12], i;
	int16_t raw_val;
	float temp_f;

	temp_sensor.reset();
	temp_sensor.select(temp_sensor_addr);			   /* Select temp sensor. */
	temp_sensor.write(0x44);							 /* Start conversion. */
	delay(1000);				     /* Wait 1sec for conversion to complete. */

	temp_sensor.reset();
	temp_sensor.select(temp_sensor_addr);			   /* Select temp sensor. */
	temp_sensor.write(0xBE);							    /* Read the data. */

	for (i = 0; i < 9; i++)
	{
		data[i] = temp_sensor.read();	          /* Read one byte at a time. */
	}

	raw_val = data[0] | (data[1] << 8);						 /* 9-bit result. */

	raw_val = (raw_val & ~0x07);
	temp_f = (((float)raw_val / 16.0) * 1.8) + 32;	  /* Compute temperature. */

	return (temp_f);
}
