/*
Kobuki.cpp - Library for interacting with the Kobuki
Created by Michael J. Conte, July 7, 2017.
Released into the public domain.
*/
#include "Arduino.h"													// gives the source file access to all arduino commands such as Serial.print
#include "Kobuki.h"

byte rx_value[44];														// creates an array that stores the most current sensor values
long previousMillis = 0;												// stores the last time rx_value was updated

void Kobuki::command(byte opcode, int sub_payload_1, int sub_payload_2)	// formats the bytestream that is being sent to the kobuki  
{
	byte data_length = 0x00;					
	byte payload[6] = {opcode, 0, 0, 0, 0, 0};							// payload is an array of the data you want to send to the kobuki
	
	if (opcode == 1)
	{
		data_length = 0x04;
		payload[1] = data_length;
		payload[2] = lowByte(sub_payload_1);							// the kobuki reads each element of the stream as a byte, therefore any value that is larger than one byte must be seperated into two one-byte elements					
		payload[3] = highByte(sub_payload_1);
		payload[4] = highByte(sub_payload_2);
		payload[5] = lowByte(sub_payload_2);
	}
	else if ( opcode == 3)
	{
		data_length = 0x03;
		payload[1] = data_length;
		payload[2] = highByte(sub_payload_1);
		payload[3] = lowByte(sub_payload_1);
		payload[4] = lowByte(sub_payload_2);
	}
	else if (opcode == 4)
	{
		data_length = 0x01;
		payload[1] = data_length;
		payload[2] = lowByte(sub_payload_1);
	}
	else if (opcode == 12)
	{
		data_length = 0x02;
		payload[1] = data_length;
		payload[2] = highByte(sub_payload_1);
		payload[3] = lowByte(sub_payload_1);
	}
	else
	{
		payload[1] = data_length;
	}
	
	int i;
	byte header1 = 0xAA, header2 = 0x55, len = 2 + data_length, len_of_packet = len + 3;	// header1/header2 let the kobuki know that this is the beginning of the bytestream
	byte checksum = 0x00, packet[len_of_packet] = {header1, header2, len};					// checksum is the result of xoring all elements of the bytestream, that lets the kobuki know id the data has been corrupted. packet is the final bytestream
		
	checksum ^= len;
	checksum ^= opcode;
	checksum ^= data_length;
	for (i = 0; i < len; i++)
	{
		checksum ^= payload[i];
	}
	for (i = 0; i < len; i++)																	
	{
		packet[i + 3] = payload[i];
	}
	packet[len + 3] = checksum;
	Serial.write(packet, len_of_packet);
}

void Kobuki::refresh_sensors()
{
	Serial.print('\n');
	Serial.print("feedback packet");
	Serial.print('\n');
	bool execution = false;											// execution lets the program know if the rx_value array has been updated
	byte checkheader1 = 0, checkheader2 = 0, interval = 20;         // interval sets how often the program will check for a bytestream from the kobuki in ms
	int counter = 0, i;													
	
	for(i = 0; i < 44; i++)
	{
		rx_value[i] = 0;
	}
	while(execution == false)										// runs through the function until the rx_value array has been updated                          
	{
		unsigned long currentMillis = millis();						// stores how long the program has been running
		if (currentMillis - previousMillis > interval)				// checks for a bytestream from the kobuki at a rate of 50Hz (every 20 ms)
		{
			while (Serial.available() > 0)
			{
				if (checkheader1 == 0xAA && checkheader2 == 0x55)	// looks for the two header values that indicate the beginning of a bytestream
				{
					if (counter >= 44)								// only pull the first 44 values after the headers 
					{
						Serial.print('\n');
						Serial.print("Break");
						Serial.print('\n');
						counter = 0;								// reset all values
						checkheader1 = 0;
						checkheader2 = 0;
						execution = true;							// let the while loop know that the rx_values has been updated
						break;										// break from current loop.
					}
					rx_value[counter] = Serial.read();				// update rx_value with current sensor outputs
					Serial.print(rx_value[counter], HEX);
					Serial.print('\n');
					counter++;										// move to the next element in the byte stream
				}
				else
				{
					checkheader1 = Serial.read();					// if the first two elements in the bytestream are not the header elements then keep checking until they are found 
					checkheader2 = Serial.read();
				}//end of header check
			}// end of serial avail while loop
			Serial.print('\n');
			Serial.print("I've infiltrated the if statment");
			Serial.print('\n');
			previousMillis += currentMillis;						// stores the time at which teh program updated the rx_value array
		}//end of timing if statement
	}
}


int Kobuki::feedback(int sensor_id)									// returns the output of a specific sensor depending on the ID the user gives.
{
	if ((sensor_id == 8) || (sensor_id == 10) || (sensor_id == 25) || (sensor_id == 27) || (sensor_id == 34) || (sensor_id == 36) || (sensor_id == 38) )	//some sensors output data longer than one byte, if the user wants one of these values then this portion concatenates the bytes together into a readable form
	{
		int value = (rx_value[sensor_id] << 8) | rx_value[sensor_id + 1];
		Serial.print('\n');
		Serial.print(" return  = ");
		Serial.print(value, HEX);
		Serial.print('\n');
		return value;
	}
	else
	{
		return (int)rx_value[sensor_id];																																
	}	
}

