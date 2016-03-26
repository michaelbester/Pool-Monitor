/******************************************************************************/
/* Project:     Pool Monitor                                                  */
/*                                                                            */
/* FileName:    adc.h         					                              */
/*                                                                            */
/* Author:      Michael Bester                                                */
/*                                                                            */
/* Overview:    This module contains the function proto-types, global vars,   */
/*              and definitions used in the adc.c module.                     */
/*                                                                            */
/* Notes:                                                                     */
/*                                                                            */
/******************************************************************************/
#ifndef _ADC_
#define _ADC_

/*************************** Function Proto-types *****************************/
uint16_t ADC_Get_Measurement(uint8_t chan, uint16_t avg_cnt);

#endif
