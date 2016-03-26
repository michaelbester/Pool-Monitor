/******************************************************************************/
/* Project:     Pool Monitor                                                  */
/*                                                                            */
/* FileName:    init.h         					                              */
/*                                                                            */
/* Author:      Michael Bester                                                */
/*                                                                            */
/* Overview:    This module contains the function proto-types, global vars,   */
/*              and definitions used in the init.c module.                    */
/*                                                                            */
/* Notes:                                                                     */
/*                                                                            */
/******************************************************************************/
#ifndef _INIT_
#define _INIT_

#include <WiFiUdp.h>
#include "OneWire.h"
#include <RTCZero.h>

/****************************** External Variables ****************************/
extern WiFiUDP Udp;
extern OneWire temp_sensor;
extern uint8_t temp_sensor_addr[8];
extern RTCZero rtc;

/******************************** Definitions *********************************/
#define WIFI_SSID				"belkin.cac"
#define WIFI_PASSWORD			"9e2b49cc"
#define UDP_PORT				2390

/*************************** Function Proto-types *****************************/
void Init(void);
void Init_Wifi(void);
void Init_UDP(void);
void Init_Temp_Sensor(void);
void Init_RTC(void);

#endif


