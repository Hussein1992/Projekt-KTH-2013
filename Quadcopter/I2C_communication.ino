void Write_I2C(int ADDRESS, byte POINTER, byte NEW){
  Wire.beginTransmission(ADDRESS);  //Begin a transmission to the I2C slave device with the given address
    Wire.write(POINTER);            //Point at a specific register
    Wire.write(NEW);                //Write the following to the register
  Wire.endTransmission();           //Ends the transmission between master (arduino) and slave (IMU)
  
}


void Read_I2C(int ADDRESS, byte POINTER, byte READ[], int AMOUNT){
  
  Wire.beginTransmission(ADDRESS);   //Begin a transmission to the I2C slave device with the given address
    Wire.write(POINTER | (1 << 7));  //Point at a specific register
  Wire.endTransmission();            // End, to start "communication" between master and slave
       
  Wire.requestFrom(ADDRESS,AMOUNT);  //Request data from a specific address plus an addition of x AMOUNT of extra data
    for(int x = 0; x < AMOUNT; x++){
      READ[x] = Wire.read();         //Reads the requested data
    }
}
