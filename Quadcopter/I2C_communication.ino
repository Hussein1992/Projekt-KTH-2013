void Write_I2C(int ADDRESS, byte POINTER, byte NEW){
  Wire.beginTransmission(ADDRESS);
    Wire.write(POINTER);
    Wire.write(NEW);
  Wire.endTransmission();
  
}


void Read_I2C(int ADDRESS, byte POINTER, byte READ[], int AMOUNT){
  
  Wire.beginTransmission(ADDRESS);
    Wire.write(POINTER | (1 << 7));
  Wire.endTransmission();
       
  Wire.requestFrom(ADDRESS,AMOUNT);    
    for(int x = 0; x < AMOUNT; x++){
      READ[x] = Wire.read();         
    }
}
