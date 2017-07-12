/*
  Line Follower Algorithm
  This program uses the center and right clif sensors on the bottom of the robot to detect and follow a line of reflective tape,
  the line of tape should be oriented inbetween the two sensors such that they are constactly detecting the floor. If the center
  cliff sensor detects a line then the kobuki turns to the left until it detects the floor, likewise if teh right sensor detects a 
  line it turns to the right. Note, the values used in the if statements will vary depending on your system, each light sensor is 
  different therefore you must measeure what values it detects as a "line" and what values it detects as the floor. 
  Written By: Michael J. Conte
  Date: July 10th 1017
*/

#include <Kobuki.h>
Kobuki kobuki;

void setup() 
{
  Serial.begin(115200);
}

void loop() 
{
  kobuki.refresh_sensors();
  if(((unsigned int)kobuki.feedback(36)) < 0xB000  && ((unsigned int)kobuki.feedback(34)) < 0x2000)
  {
    kobuki.command(1, 100, 0);
    
  }
  else if(((unsigned int)kobuki.feedback(36)) > 0xC000 && ((unsigned int)kobuki.feedback(34)) < 0x2000)
  {
    kobuki.command(1, 100, 0xFFFF);
    
  }
  else if(((unsigned int)kobuki.feedback(36)) < 0xB000 && ((unsigned int)kobuki.feedback(34)) > 0x3000)
  {
    kobuki.command(1, -100, 0xFFFF);
  }
}
