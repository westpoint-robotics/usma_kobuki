/*
Kobuki.h - Library for interacting with the Kobuki
Created by Michael J. Conte, July 7, 2017.
Released into the public domain.
*/
#ifndef Kobuki_h
#define Kobuki_h
#include "Arduino.h"

class Kobuki
{
  public:    
    void command(byte opcode, int sub_payload_1, int sub_payload_2 = NULL);
    void refresh_sensors();
    int feedback(int sensor_id);
  private:
    byte rx_value[44];
    long previousMillis = 0;
};

#endif
