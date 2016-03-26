/******************************************************************************/
/* Project:     Pool Monitor                                           	      */
/*                                                                            */
/* FileName:    init.ino		                                              */
/*                                                                            */
/* Author:      Michael Bester                                                */
/*                                                                            */
/* Overview:    This module contains the initialization code for the project. */
/*				functions.													  */
/*                                                                            */
/* Notes:                                                                     */
/*                                                                            */
/******************************************************************************/

/***************************** Include Files **********************************/
#include <wiring_analog.h>
#include <WiFi101.h>
#include <WiFiUdp.h>
#include <OneWire.h>
#include <RTCZero.h>
#include "init.h"

WiFiUDP Udp;
OneWire temp_sensor(0);
uint8_t temp_sensor_addr[8];
RTCZero rtc;

/******************************************************************************/
/* Function:    void Init(void)                  	                          */
/*                                                                            */
/* Inputs:      None.                                                         */
/*                                                                            */
/* Outputs:     None.                                                         */
/*                                                                            */
/* Description: This function initializes the system.		                  */
/*                                                                            */
/* Author:      Michael Bester                                                */
/*                                                                            */
/* Notes:       This function calls device specific device dependent init	  */
/*				functions.          										  */
/*                                                                            */
/******************************************************************************/
void Init(void)
{
	Init_ADC();
	Init_Wifi();
	Init_UDP();
	Init_Temp_Sensor();
	Init_RTC();
}

/******************************************************************************/
/* Function:    void Init_ADC(void)               	                          */
/*                                                                            */
/* Inputs:      None.                                                         */
/*                                                                            */
/* Outputs:     None.                                                         */
/*                                                                            */
/* Description: This function initializes the AtoD converter peripheral.      */
/*                                                                            */
/* Author:      Michael Bester                                                */
/*                                                                            */
/* Notes:																	  */
/*                                                                            */
/******************************************************************************/
void Init_ADC(void)
{
	analogReference(AR_DEFAULT);	     	   /* Use default 3.3V reference. */
	analogReadResolution(10);		  /* Read analog values as 10-bit values. */
}

/******************************************************************************/
/* Function:    void Init_Wifi(void)               	                          */
/*                                                                            */
/* Inputs:      None.                                                         */
/*                                                                            */
/* Outputs:     None.                                                         */
/*                                                                            */
/* Description: This function initializes the Wifi radio peripheral.	      */
/*                                                                            */
/* Author:      Michael Bester                                                */
/*                                                                            */
/* Notes:																	  */
/*                                                                            */
/******************************************************************************/
void Init_Wifi(void)
{
	uint8_t result = WL_IDLE_STATUS;
	long rssi;
	byte mac[6];
	IPAddress ip_addr;

	while (result != WL_CONNECTED)			  /* Wait for network connection. */
	{
		result = WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
		delay(10000);
	} 

	rssi = WiFi.RSSI();

	Serial.print("RSSI: ");						    /* Send RSSI information. */
	Serial.println(rssi);

	WiFi.macAddress(mac);					  /* Send unit's MAC information. */
	Serial.print("MAC: ");
	Serial.print(mac[5], HEX);
	Serial.print(":");
	Serial.print(mac[4], HEX);
	Serial.print(":");
	Serial.print(mac[3], HEX);
	Serial.print(":");
	Serial.print(mac[2], HEX);
	Serial.print(":");
	Serial.print(mac[1], HEX);
	Serial.print(":");
	Serial.println(mac[0], HEX);

	ip_addr = WiFi.localIP();					 /* Send assigned IP address. */
	Serial.print("IP Address: ");
	Serial.println(ip_addr);

}

/******************************************************************************/
/* Function:    void Init_UDP(void)               	                          */
/*                                                                            */
/* Inputs:      None.                                                         */
/*                                                                            */
/* Outputs:     None.                                                         */
/*                                                                            */
/* Description: This function initializes the UDP interface.			      */
/*                                                                            */
/* Author:      Michael Bester                                                */
/*                                                                            */
/* Notes:																	  */
/*                                                                            */
/******************************************************************************/
void Init_UDP(void)
{
	uint8_t result = 0;
	
	while (result == 0)
	{
		result = Udp.begin(UDP_PORT);	  /* Bind UDP service to port number. */
	}
	Serial.println("UDP successful.");
}

/******************************************************************************/
/* Function:    void Init_Temp_Sensor(void)               	                  */
/*                                                                            */
/* Inputs:      None.                                                         */
/*                                                                            */
/* Outputs:     None.                                                         */
/*                                                                            */
/* Description: This function initializes the one-wire temperature sensor     */
/*				interface.													  */
/*                                                                            */
/* Author:      Michael Bester                                                */
/*                                                                            */
/* Notes:		Using digital pin 0 for the one wire interface.			      */
/*                                                                            */
/******************************************************************************/
void Init_Temp_Sensor(void)
{
	int result, i;

	result = temp_sensor.search(temp_sensor_addr);		        /* Read info. */

	if (result == 0)
	{
		Serial.println("Couldn't find the temperature sensor!");
	}
	else
	{
		Serial.println("Temperature sensor found!");
	}

}

/******************************************************************************/
/* Function:    void Init_RTC(void)			            	                  */
/*                                                                            */
/* Inputs:      None.                                                         */
/*                                                                            */
/* Outputs:     None.                                                         */
/*                                                                            */
/* Description: This function initializes the RTC peripheral.			      */
/*                                                                            */
/* Author:      Michael Bester                                                */
/*                                                                            */
/* Notes:																      */
/*                                                                            */
/******************************************************************************/
void Init_RTC(void)
{
	rtc.begin();
	rtc.setTime(0, 0, 0);
	rtc.setDate(0, 0, 0);
	rtc.setAlarmTime(0, 0, 5);
	rtc.attachInterrupt(alarmMatch);
}