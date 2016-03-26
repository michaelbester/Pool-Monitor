/******************************************************************************/
/* Project:     Pool Monitor                                           	      */
/*                                                                            */
/* FileName:    adc.cpp			                                              */
/*                                                                            */
/* Author:      Michael Bester                                                */
/*                                                                            */
/* Overview:    This module contains the analog to digital converter code.    */
/*				functions.													  */
/*                                                                            */
/* Notes:                                                                     */
/*                                                                            */
/******************************************************************************/

/***************************** Include Files **********************************/
#include <wiring_analog.h>
#include "adc.h"

/******************************************************************************/
/* Function:    uint16_t ADC_Get_Measurement(uint8_t pin, uint16_t avg_cnt)   */
/*                                                                            */
/* Inputs:      pin:		Analog pin to take reading.                       */
/*				avg_cnt:	Number of samples to average.					  */
/*                                                                            */
/* Outputs:     Computed AtoD average read value.                             */
/*                                                                            */
/* Description: This function will average a given number of atod samples and */
/*				return it's result.											  */
/*                                                                            */
/* Author:      Michael Bester                                                */
/*                                                                            */
/* Notes:																	  */
/*                                                                            */
/******************************************************************************/
uint16_t ADC_Get_Measurement(uint8_t pin, uint16_t avg_cnt)
{
	uint32_t val = 0;
	uint16_t i, result;

	for (i = 0; i < avg_cnt; i++)    /* Get specified number of measurements. */
	{
		val += analogRead(pin);	      /* Get ADC measurement of selected pin. */
	}

	result = (val / avg_cnt);					    /* Compute average value. */

	return (result);
}