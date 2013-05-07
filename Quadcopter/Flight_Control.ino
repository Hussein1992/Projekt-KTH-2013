 // PID    :
 //   *     Stick inputs (Roll and Pitch) will be mapped from 1000 - 2000 to -45 to +45 degrees. Called setpoints.
 //   *     Gyroscope and accelerometers will be combined using compl. filter to get filtered angles (The attitude of the object). Called Input.
 //   *     These values will be processed through a PID regulator.
 //   *     The output from the PID regulator will be mixed with the Throttle power for each motor.  


void Process_Stabilize(){  
    time_actual = millis();
    time_change = time_actual - time_last;
    
    //Repeat with a frequency of 100Hz (10000uS, 10mS, 0.01S)
    if(time_change >= 10){

        // Read stick inputs 
        rc_read();    
        
        noInterrupts();  // Make sure that the interrupts doesn't interfer with sensor reading
        // Read sensor data
        ADXL345_read();
        L3G4200D_read();
        
        // Combine gyroscope and accelerometer values with complementary filter ( degrees)
        Complementary_roll  = (0.93*(Complementary_roll+(L3G4200D_DPS_x*(double)(micros()-sensor_timer)/1000000))) + (0.07*ACCEL_roll);  
        Complementary_pitch = (0.93*(Complementary_pitch+(L3G4200D_DPS_y*(double)(micros()-sensor_timer)/1000000))) + (0.07*ACCEL_pitch);  
        sensor_timer = micros();
        
        // Map roll and pitch to +/- 45 degrees
        RC_Mapped_Roll  = map(rc_values[ROLL], MINCOMMAND, MAXCOMMAND, MIN_ANGLE, MAX_ANGLE);
        RC_Mapped_Pitch = map(rc_values[PITCH], MINCOMMAND, MAXCOMMAND, MIN_ANGLE, MAX_ANGLE);
        
        // Process PID regulator
        PID_calculate();
        
        time_last = time_actual;
        
        interrupts(); // Enable interrupts
    }
     
}
