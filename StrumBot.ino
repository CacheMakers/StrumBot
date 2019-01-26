/*
 * Simple robot to strum a ukelele
 * Uses a micro servo and an Arduino Uno
 * Arduino is equipped with a power switch and five buttons
 * The first two buttons adjust strumming speed
 * The other three are for selecting from several pre-programmed
 * cadences or patterns (THIS FEATURE NOT YET IMPLEMENTED)
 */

#include <Servo.h>

// pin declarations
int spdUp = 4;
int spdDn = 5;
int mode1 = 6;
int mode2 = 7;
int mode3 = 8;
int srvPn = 10;

// servo object
Servo myservo;

// system variables
int mode = 1;     // current mode - to be implemented later
int pos = 0;      // position of arm
int minPos = 30;  // minimum position
int maxPos = 150; // maximum position
int per = 15;     // period between arm movements - lower values strum faster
int minPer = 0;   // minium period - defines max speed
int maxPer = 100; // maximum period - defines min speed
int stpPer = 5;   // step for period adjustments - higher values change speed faster

// helper function - delays for given time, but polls and handles button presses
// once every 1 ms.
void delayRead(int dur)
{
  for(int i=0; i<dur; i++)
  {
    // adjust tempo
    if(digitalRead(spdUp) == LOW && per > minPer)
    {
      per -= stpPer;
    }
    if(digitalRead(spdDn) == LOW && per < maxPer)
    {
      per += stpPer;
    }

    // change modes - to be implemented later
  }
}

void setup() 
{
  // set pinmodes, attach servo
  pinMode(spdUp, INPUT_PULLUP);
  pinMode(spdDn, INPUT_PULLUP);
  pinMode(mode1, INPUT_PULLUP);
  pinMode(mode2, INPUT_PULLUP);
  pinMode(mode3, INPUT_PULLUP);
  myservo.attach(srvPn);
}

void loop() 
{
  for (pos = minPos; pos <= maxPos; pos += 1) 
  {
    myservo.write(pos);
    delayRead(per);
  }
  for (pos = maxPos; pos >= minPos; pos -= 1) 
  {
    myservo.write(pos);
    delayRead(per);
  }
}

