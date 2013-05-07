/////////////////////////////////////////////////////////////////////
///////////////////////// PID - FAILSAFE ///////////////////////////
///////////////////////////////////////////////////////////////////
void PID_calculate(){
  float time_actual = millis();
  float time_change = time_actual - time_last;
  
  // Repeat with a frequency of 100Hz (10000uS, 10mS, 0.01S)
  if(time_change >= sample_time){
    
    PID_calculate_step2(PID_ROLL);
    PID_calculate_step2(PID_PITCH);
    
    time_last       = time_actual;
  }  
}
/////////////////////////////////////////////////////////////////////
///////////////////////// PID - COMPUTE/ ///////////////////////////
///////////////////////////////////////////////////////////////////
void PID_calculate_step2(double PID_BUFFER[]){
  
    // The proportional error -> Difference between our setpoint and current position
    error_prop      = PID_BUFFER[SETPOINT] - PID_BUFFER[P_INPUT];
    
    // The intergral error -> A summation of the errors
    error_integral += error_prop;    
    
    // The derivate error -> The difference between current position and last error
    error_derivata  = PID_BUFFER[P_INPUT] - PID_BUFFER[LAST_INPUT];
    
    // OUTPUT -> A summation of the PID parameters, where each parameter is multiplied with a gainfactor
    PID_BUFFER[P_OUTPUT]   = PID_BUFFER[KP]*error_prop + PID_BUFFER[KI]*error_integral + PID_BUFFER[KD]*error_derivata;    
    
    // Saving our current error, for next derivate error
    PID_BUFFER[LAST_INPUT] = PID_BUFFER[P_INPUT];
  
}
/////////////////////////////////////////////////////////////////////
///////////////////////// PID - INITIALIZE ///////////////////////////
///////////////////////////////////////////////////////////////////
void PID_sample_init(double PID_BUFFER[]){ 
  float  sample_time_sec = sample_time/1000;
  
  // Nuvarande fel
  PID_BUFFER[KP] = PID_BUFFER[KP];
  
  // integral = dx*dt -> 
  PID_BUFFER[KI] = PID_BUFFER[KI]*sample_time_sec;
  
  // derivata = dx/dt -> dividera med tiden/sample tiden
  PID_BUFFER[KD] = PID_BUFFER[KD]/sample_time_sec;   
  
}


