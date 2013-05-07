/////////////////////////////////////////////////////////////////////
/////////////// INITIALIZING OF GYROSCOPE ///////////////////////////
////////////////////////////////////////////////////////////////////
void L3G4200D_init(){
  Read_I2C(L3G4200D_ADDR, L3G4200D_WHO_AM_I, buffer, 1);   // READS THE DEVICE_ID
  DEV_ID = buffer[0];
  
  // Verify that the accelerometer is connected properly
  if(DEV_ID = 211){
    Serial.println("L3G4200D: CONNECTED"); 
    Write_I2C(L3G4200D_ADDR, L3G4200D_CTRL_REG1, 0x00); // Power off sensor
    Write_I2C(L3G4200D_ADDR, L3G4200D_CTRL_REG1, 0x0F); // 0000 1111(f = 100hz, B = 12.5) Sensor and all axis ON  
    Write_I2C(L3G4200D_ADDR, L3G4200D_CTRL_REG2, 0x00); // 0010 0000 Normal mode on  
    Write_I2C(L3G4200D_ADDR, L3G4200D_CTRL_REG3, 0x08); // FIFO and interrupts off  
    Write_I2C(L3G4200D_ADDR, L3G4200D_CTRL_REG4, 0x30); // 0011 000 (2000 DPS)  
    Write_I2C(L3G4200D_ADDR, L3G4200D_CTRL_REG5, 0x00); // 0000 0000 FIFO and highpass-filter OFF 
    
    // Take the average of 250 samples -> Our offset for each axis
    delay(100);
    Serial.println("Calibrating L3G4200D");
    for(int x = 0; x < 250; x++){
       Read_I2C(L3G4200D_ADDR, L3G4200D_OUT_X_L, buffer, 6);    //Read x,y,z axis. Each axis has two variables with 1 byte each -> x0,x1 || y0,y1 || z0,z1
        
       // Word(x1,x0) -> Combine the variables into one variable -> 1bye + 1byte = 2 bytes
       L3G4200D_x = (word(buffer[1], buffer[0])) + L3G4200D_x;  // A total of 250 samples
       L3G4200D_y = (word(buffer[3], buffer[2])) + L3G4200D_y;
       L3G4200D_z = (word(buffer[5], buffer[4])) + L3G4200D_z;

    }
    
    // Divide by 250 to get the average 
    L3G4200D_OFFSET_x = L3G4200D_x/250;
    L3G4200D_OFFSET_y = L3G4200D_y/250;
    L3G4200D_OFFSET_z = L3G4200D_z/250;
  }
  else{ Serial.println("L3G4200D: DISCONNECTED"); }       
  
}
/////////////////////////////////////////////////////////////////////
/////////////// READ VALUES AND COMPUTE GYROSCOPE ///////////////////
////////////////////////////////////////////////////////////////////
void L3G4200D_read(){
  Read_I2C(L3G4200D_ADDR, L3G4200D_OUT_X_L, buffer, 6);  //Read x,y,z axis
  
  // Combine each axis with their two varialbes into one
  L3G4200D_x = (word(buffer[1], buffer[0]));
  L3G4200D_y = (word(buffer[3], buffer[2]));
  L3G4200D_z = (word(buffer[5], buffer[4]));
  
  // Subtracting with the offset/bias to get correct position.
  L3G4200D_CALIB_x = L3G4200D_x - L3G4200D_OFFSET_x;
  L3G4200D_CALIB_y = L3G4200D_y - L3G4200D_OFFSET_y;
  L3G4200D_CALIB_z = L3G4200D_z - L3G4200D_OFFSET_z;
  
  // Multiplying with a gain factor to convert to degrees/s
  L3G4200D_DPS_x = L3G4200D_CALIB_x * 0.07;
  L3G4200D_DPS_y = L3G4200D_CALIB_y * 0.07;
  L3G4200D_DPS_z = L3G4200D_CALIB_z * 0.07;

}
/////////////////////////////////////////////////////////////////////
/////////////// WRITE RAW, G'S AND DEGREES /////////////////////////
////////////////////////////////////////////////////////////////////
void L3G4200D_write(int x, int y, int z){
      
      if(x==1){
       Serial.print("GYRO RAW CALIB");               Serial.print("  X:   ");
       Serial.print(L3G4200D_CALIB_x);          Serial.print("  Y:   "); 
       Serial.print(L3G4200D_CALIB_y);          Serial.print("  Z:   "); 
       Serial.print(L3G4200D_CALIB_z);          Serial.print("       ");
      }
      if(y==1){
       Serial.print("  GYRO DPS    X:");
       Serial.print(L3G4200D_DPS_x);               Serial.print("   Y:   "); 
       Serial.print(L3G4200D_DPS_y);               Serial.print("   Z:   "); 
       Serial.print(L3G4200D_DPS_z); 
      }
      if(z==1){
       Serial.print("   GYRO DEGREE    PITCH:");
       Serial.print(GYRO_pitch);      Serial.print("   ROLL:   "); 
       Serial.print(GYRO_roll);
      }
  
}



