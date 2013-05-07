/////////////////////////////////////////////////////////////////////
/////////////// INITIALIZE MOTORS/ESC'S ////////////////////////////
///////////////////////////////////////////////////////////////////
void Motor_Initialize(){  
  // Initiliaze all timers, except timer2
  InitTimersSafe();
  // Each output generates a PWM signal with 200hz
  SetPinFrequencySafe(12, 200);  //Front
  SetPinFrequencySafe(11,200);   //Back
  SetPinFrequencySafe(6,200);    //Left
  SetPinFrequencySafe(5,200);   //Right
  
  // 49 = 1000uS -> All motors off / start sequense for ESC's
  pwmWrite(12, 49);
  pwmWrite(11, 49);
  pwmWrite(5, 49);
  pwmWrite(6, 49);
  
  // Make sure the ESC's initiliazes
  delay(2000);  
  
}
/////////////////////////////////////////////////////////////////////
///////////////////////// MIX TABLE ////////////////////////////////
///////////////////////////////////////////////////////////////////
void Mix_Motor_Output(){
   
   // Failsafe routine, if out of interval -> motor off 
   if(rc_values[THROTTLE] > MINCOMMAND || rc_values[THROTTLE] < MAXCOMMAND & ){
   //Make sure that the values stays within the ESC interval , 1000uS - 2000uS
   ESC_MOTOR_OUTPUT[FRONT] = constrain((rc_values[THROTTLE] - PID_PITCH[P_OUTPUT]), 1025, 1950);
   ESC_MOTOR_OUTPUT[BACK]  = constrain((rc_values[THROTTLE] + PID_PITCH[P_OUTPUT]), 1025, 1950);
   ESC_MOTOR_OUTPUT[LEFT]  = constrain((rc_values[THROTTLE] - PID_ROLL[P_OUTPUT]),  1025, 1950);
   ESC_MOTOR_OUTPUT[RIGHT] = constrain((rc_values[THROTTLE] + PID_ROLL[P_OUTPUT]),  1025, 1950);
   }
   else{
     ESC_MOTOR_OUTPUT[FRONT] = 1025;
     ESC_MOTOR_OUTPUT[BACK]  = 1025;
     ESC_MOTOR_OUTPUT[LEFT]  = 1025;
     ESC_MOTOR_OUTPUT[RIGHT] = 1025;
   }
   
   
  
}
/////////////////////////////////////////////////////////////////////
//////////////// WRITE VALUES TO MOTOR/ESC /////////////////////////
///////////////////////////////////////////////////////////////////
void Write_Motor(){
   
   //A factor of 0.052 will be multiplied to the OUTPUT value to get the right PWM signals
   pwmWrite(12,  (ESC_MOTOR_OUTPUT[FRONT]*0.052));
   pwmWrite(11, (ESC_MOTOR_OUTPUT[BACK]*0.052));
   pwmWrite(6,  (ESC_MOTOR_OUTPUT[LEFT]*0.052));
   pwmWrite(5, (ESC_MOTOR_OUTPUT[RIGHT]*0.052));
  
}
