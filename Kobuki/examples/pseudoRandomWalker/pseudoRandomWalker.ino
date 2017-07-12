/*
  Random Walker Algorithm
  This program commands the kobuki to move forward until it detects on obstacle using the bumper sensors,
  if an obstacle is detected then the kobuki will back up, turn to the right until it has cleared the
  obstacle then it will continue moving forward.
  Written By: Michael J. Conte
  July 10th 2017
*/

#include <Kobuki.h>
Kobuki kobuki;

void setup()
{
  Serial.begin(115200);
}

void loop()
{
  long timer = 0, reversestop = 500, reversestart = 0, turnstart = 0, turnstop = 500;
  kobuki.refresh_sensors();

  if (kobuki.feedback(5) != 0)
  {
    reversestart = millis();
    while (reversestart + reversestop > timer)
    {
      timer = millis();
      kobuki.command(1, -100, 0);
    }
    timer = 0;
    turnstart = millis();
    while (turnstart + turnstop > timer)
    {
      timer = millis();
      kobuki.command(1, 100, 0xFFFF);
    }
    turnstart = 0;
  }
  else
  {
    kobuki.command(1, 100, 0);
  }
}
