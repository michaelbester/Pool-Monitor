/******************************************************************************/
/* Project:     Pool Monitor                                           	      */
/*                                                                            */
/* FileName:    pool_monitor.ino                                              */
/*                                                                            */
/* Author:      Michael Bester                                                */
/*                                                                            */
/* Overview:    This module contains both the arduino setup() and loop()      */
/*				functions.													  */	
/*                                                                            */
/* Notes:                                                                     */
/*                                                                            */
/******************************************************************************/

/****************************** Definitions ***********************************/
//#define NO_COMP									 /* No compensation flag. */
#define ADC_PIN		0					     	/* ADC pin number to read ph. */
#define AVG_COUNT	10					   /* Number of measurements to take. */

/***************************** Include Files **********************************/
#include <WiFiSSLClient.h>
#include <WiFiServer.h>
#include <WiFiClient.h>
#include <WiFi101.h>
#include <WiFiUdp.h>
#include <Wire.h>
#include "temp_sensor.h"
#include "init.h"
#include "adc.h"
#include <RTCZero.h>

/******************************************************************************/
/* Function:    void setup()	                 	                          */
/*                                                                            */
/* Inputs:      None.                                                         */
/*                                                                            */
/* Outputs:     None.                                                         */
/*                                                                            */
/* Description: The setup() function is called when a sketch starts. Use it   */
/*				to initialize variables, pin modes, start using libraries,    */
/*				etc. The setup function will only run once, after each		  */
/*				powerup or reset of the Arduino board.		                  */
/*                                                                            */
/* Author:      Michael Bester                                                */
/*                                                                            */
/* Notes:       This function calls device specific device dependent init	  */
/*				functions.          										  */
/*                                                                            */
/******************************************************************************/
void setup() 
{
	Init();									   /* Initialize microcontroller. */
	pinMode(7, OUTPUT);
	digitalWrite(7, LOW);
}

void loop()
{
	uint8_t whole_digit, fraction;
	static char ph_str[32];
	static char temp_str[32];
	static char rssi_str[32];
	static char msg_cnt_str[32];
	static long rssi;
	static float ph;
	static uint16_t raw_adc;
	static float temp_f;						 
	static float temp_c;
	static uint32_t cycle_count = 0;


	if (cycle_count % 12 == 0)
	{
		temp_f = Read_Temperature();
		temp_c = (5.0 / 9.0)*(temp_f - 32.0);

		digitalWrite(7, HIGH);
		delay(1000);
		raw_adc = ADC_Get_Measurement(ADC_PIN, AVG_COUNT);
		digitalWrite(7, LOW);

		ph = 7.0 - ((2.5 - (float)((raw_adc / 1024.0)*3.3)) / (0.257179 + (0.000941468*temp_c)));

#ifdef DEBUG
		rssi = WiFi.RSSI();										 /* Get the RSSI. */
		sprintf(rssi_str, "RSSI Value: %d\n", rssi);
#endif

		temp_f = Read_Temperature();						 /* Read temperature. */
		temp_f *= 10;
		temp_c *= 10;

		whole_digit = (int)temp_c / 10;				/* Create temperature string. */
		fraction = temp_c - (float)(whole_digit * 10.0);
		sprintf(temp_str, "Temperature: %d.%dC\n", whole_digit, fraction);

		ph = ph * 10;										 /* Create PH string. */
		whole_digit = (int)ph / 10;
		fraction = ph - (float)(whole_digit * 10);
		sprintf(ph_str, "PH:  %d.%d\n", whole_digit, fraction);
	}

	cycle_count++;

#ifdef DEBUG
	sprintf(msg_cnt_str, "Message Count: %d\n", cycle_count);
#endif

	Udp.beginPacket((const char*)"255.255.255.255", UDP_PORT);  
	Udp.write(ph_str);							/* Send data out the network. */
	Udp.write(temp_str);

#ifdef DEBUG
	Udp.write(rssi_str);
	Udp.write(msg_cnt_str);
#endif

	Udp.endPacket();
	delay(1000);

#ifdef DEBUG
	Serial.print(ph_str);
	Serial.print(temp_str);
	Serial.print(rssi_str);
	Serial.print(msg_cnt_str);
#endif

	rtc.setTime(0, 0, 0);
	rtc.enableAlarm(rtc.MATCH_SS);
	rtc.standbyMode();
}

void alarmMatch(void)
{

}