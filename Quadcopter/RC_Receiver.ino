/////////////////////////////////////////////////////////////////////
/////////////// INITIALIZING OF INTERRUPT //////////////////////////
////////////////////////////////////////////////////////////////////
void Init_RC_receiver(){
  
  // If any of these has been interrupted it will call a specific function (Can be found in "INTERRUPT OCCURED  STEP 1")
  attachInterrupt(rc_pins[ROLL],           rc_interrupt_ROLL,       CHANGE);
  attachInterrupt(rc_pins[PITCH],          rc_interrupt_PITCH,      CHANGE);
  attachInterrupt(rc_pins[THROTTLE],       rc_interrupt_THROTTLE,   CHANGE);
  attachInterrupt(rc_pins[YAW],            rc_interrupt_YAW,        CHANGE);


}
/////////////////////////////////////////////////////////////////////
///////////////     INTERRUPT OCCURED  STEP 1    ////////////////////
///////////////////////////////////////////////////////////////////
void rc_interrupt_ROLL  (){ 
  rc_interrupt(ROLL);  
}
void rc_interrupt_PITCH    (){ 
  rc_interrupt(PITCH);    
}
void rc_interrupt_THROTTLE (){ 
  rc_interrupt(THROTTLE); 
}
void rc_interrupt_YAW      (){ 
  rc_interrupt(YAW);      
}
///////////////////////
/////   STEP 2  //////
/////////////////////
void rc_interrupt(int channel){  
  if(digitalRead(rc_pins[channel])==1){  // Registers the pulse of a channel when it goes high
    timer[channel] = micros(); 
  }
  else{
    timer_hold[channel] = (micros()-timer[channel]);  // When the channel goes low, it takes the difference in time to get the pulse width
    common_flag = 1;
    rc_flag[channel] = 1;


  } 
}
/////////////////////////////////////////////////////////////////////
/////////////// READ THE VALUES FROM RECEIVER //////////////////////
////////////////////////////////////////////////////////////////////
void rc_read(){
  // If any flag has been interrupted the common flag goes high -> new values to read
  if(common_flag == 1){
    noInterrupts();  // Make sure that the interrupts doesn't interfere when we read the values of the channels
    
    // Checks which channel has been interrupted and reads the specific rc value
    if(rc_flag[ROLL]      == 1){       rc_values[ROLL]      = timer_hold[ROLL];         }
    if(rc_flag[PITCH]     == 1){       rc_values[PITCH]     = timer_hold[PITCH];        }
    if(rc_flag[THROTTLE]  == 1){       rc_values[THROTTLE]  = timer_hold[THROTTLE];     }
    if(rc_flag[YAW]       == 1){       rc_values[YAW]       = timer_hold[YAW];          }


  }
  
  // Reset the flags
  common_flag = 0;
  rc_flag[0,1,2,3] = 0;

  interrupts();  // Enabling interrupts again
}
/////////////////////////////////////////////////////////////////////
/////////////// PRINT THE VALUES FROM RECEIVER /////////////////////
////////////////////////////////////////////////////////////////////
void rc_print(){

  for(int x = 0; x < 4; x++){
    Serial.print(rc_values[x]);
    Serial.print("       ");
  }  
  Serial.println();
}






