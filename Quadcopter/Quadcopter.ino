/*
OBS! Please note that all libraries do not belong to us. Libraries that do not belong to us, are the following:
PWM.h
PinChangeInt.h
Wire.h
math.h
*/

#include <PWM.h>
#include "PinChangeInt.h"
#include "variables.h"
#include "Wire.h"
#include "math.h"


void setup(){
  Serial.begin(9600);
  
  // Initiliaze
  Init_RC_receiver();
  ADXL345_init();
  L3G4200D_init();
  PID_sample_init(PID_ROLL);
  Motor_Initialize();
 
  delay(100);
  sensor_timer = micros();
}


void loop(){  
  
    // Can be found in tab "Flight Control"
    Process_Stabilize();

 }


