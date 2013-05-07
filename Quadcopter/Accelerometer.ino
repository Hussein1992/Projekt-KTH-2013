/////////////////////////////////////////////////////////////////////
/////////////// INITIALIZING OF ACCELEROMETER ///////////////////////
////////////////////////////////////////////////////////////////////
void ADXL345_init(){
  Read_I2C(ADXL345_ADDR, ADXL345_WHO_AM_I, buffer, 1);   // READS THE DEVICE_ID
  DEV_ID = buffer[0];
  
  // Verify that the accelerometer is connected properly
  if(DEV_ID = 229){
    Serial.print("ADXL345: CONNECTED       "); 
    Write_I2C(ADXL345_ADDR, ADXL345_POWER_CTL, 0x00);     // Sensor OFF
    Write_I2C(ADXL345_ADDR, ADXL345_POWER_CTL, 0x08);     // 0001 1000 Measuring ON, checks inactivity each  0.125s (f = 8hz) and autosleep enabled
    Write_I2C(ADXL345_ADDR, ADXL345_DATA_FORMAT, 0x03);   // 0000 0011 Sensitivity +-16g
    
    // Take the average of 250 samples -> Our offset for each axis
    delay(11.1);
    Serial.println("Calibrating ADXL345");
    for(int x = 0; x < 250; x++){
       Read_I2C(ADXL345_ADDR, ADXL345_OUT_X_L, buffer, 6);    //Read x,y,z axis. Each axis has two variables with 1 byte each -> x0,x1 || y0,y1 || z0,z1

       // Word(x1,x0) -> Combine the variables into one variable -> 1bye + 1byte = 2 bytes
       ADXL345_x = (word(buffer[1], buffer[0])) + ADXL345_x;  // A total of 250 samples
       ADXL345_y = (word(buffer[3], buffer[2])) + ADXL345_y;
       ADXL345_z = (word(buffer[5], buffer[4])) + ADXL345_z;
              
    }
    
    // Divide by 250 to get the average 
    ADXL345_OFFSET_x = ADXL345_x/250;
    ADXL345_OFFSET_y = ADXL345_y/250;
    ADXL345_OFFSET_z = (ADXL345_z/250) - 32;  // Subtract 32 to get the Z axis to zero position (gravity)
  }
  else{ Serial.print("ADXL345: DISCONNECTED       "); }
    
}
/////////////////////////////////////////////////////////////////////
/////////////// READ VALUES AND COMPUTE ACCELEROMETER ///////////////
////////////////////////////////////////////////////////////////////
void ADXL345_read(){
  Read_I2C(ADXL345_ADDR, ADXL345_OUT_X_L, buffer, 6);  //Read x,y,z axis
       
       // Combine each axis with their two varialbes into one
       ADXL345_x = word(buffer[1], buffer[0]);
       ADXL345_y = word(buffer[3], buffer[2]);
       ADXL345_z = word(buffer[5], buffer[4]);
       
       // Subtracting with the offset/bias to get correct position.
       ADXL345_CALIB_x = ADXL345_x - ADXL345_OFFSET_x;
       ADXL345_CALIB_y = ADXL345_y - ADXL345_OFFSET_y;
       ADXL345_CALIB_z = ADXL345_z - ADXL345_OFFSET_z; 
       
       // Multiplying with a gain factor to convert to g's 
       ADXL345_G_x = ADXL345_CALIB_x * 0.0312;
       ADXL345_G_y = ADXL345_CALIB_y * 0.0312;
       ADXL345_G_z = ADXL345_CALIB_z * 0.0312;      
       
       // Conert from g's to degrees
       ACCEL_pitch = (((atan2(ADXL345_G_x,ADXL345_G_z))+PI)*57.2957786)-180;
       ACCEL_roll  = (((atan2(ADXL345_G_y,ADXL345_G_z))+PI)*57.2957786)-180;             
  
}
/////////////////////////////////////////////////////////////////////
/////////////// WRITE RAW, G'S AND DEGREES /////////////////////////
////////////////////////////////////////////////////////////////////
void ADXL345_write(int x, int y, int z){
    
      if(x==1){
       Serial.print("ACCEL CALIB RAW");               Serial.print("  X:   ");
       Serial.print(ADXL345_CALIB_x);          Serial.print("  Y:   "); 
       Serial.print(ADXL345_CALIB_y);          Serial.print("  Z:   "); 
       Serial.print(ADXL345_CALIB_z);          Serial.print("       ");
      }
      if(y==1){
       Serial.print("  ACCEL G's    X:");
       Serial.print(ADXL345_G_x);               Serial.print("   Y:   "); 
       Serial.print(ADXL345_G_y);               Serial.print("   Z:   "); 
       Serial.print(ADXL345_G_z); 
      }
      if(z==1){
       Serial.print("   ACCEL DEGREE    PITCH:");
       Serial.print(ACCEL_pitch);      Serial.print("   ROLL:   "); 
       Serial.print(ACCEL_roll);
      }
}
