/*
//////////////////////////////////
/////////RC RECEVIER/////////////
////////////////////////////////
Init_RC_receiver();
rc_read();
rc_print();
/////////////////////////////////////
////////////IMU SENSOR//////////////
///////////////////////////////////
ADXL345_init()
ADXL345_read()
ADXL345_write(int x, int z, int y) // RAW, G's, DEGREEE

L3G4200D_init
L3G4200D_read
L3G4200D_write(int x, int z, int y)

Write_I2C(int ADDRESS, byte POINTER, byte NEW)
Read_I2C(int ADDRESS, byte POINTER, byte READ[], int AMOUNT)
ead_I2C_Val(int ADDRESS, byte POINTER, byte READ[], int AMOUNT)

/////////////////////////////////////
////////////PID REGULATOR///////////
///////////////////////////////////
PID_sample_init(PID_X), X = ROLL, PITCH, YAW
PID_calculate()

/////////////////////////////////////
////////////MOTOR/ESC //////////////
///////////////////////////////////
Motor_Initialize()
Mix_Motor_Output()
Write_Motor()

THROTTLE = 1060 - 1900
YAW      = 964 -1972
PITCH    = 1048 - 1888
ROLL     = 1060 - 1900

ESC      = ~1185 för att starta motorn
OBS! I MILLISEKUNDER


*/
