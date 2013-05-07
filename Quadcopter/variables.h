////////////////////////////
////////RECEIVER////////////
////////////////////////////
#define ROLL        0  
#define PITCH       1
#define THROTTLE    2
#define YAW         3


#define ROLL_PIN        0 // pin 2  
#define PITCH_PIN       1 // pin 3
#define THROTTLE_PIN    4 // pin 19
#define YAW_PIN         5 // pin 18

int rc_pins[5]                          = {ROLL_PIN, PITCH_PIN, THROTTLE_PIN, YAW_PIN};
int rc_values[4]                        = {0, 0, 0, 0};
volatile int rc_flag[4]                 = {0, 0, 0, 0};
volatile uint16_t timer_hold[4]         = {0, 0, 0, 0};
volatile uint32_t timer[4]              = {0, 0, 0, 0};
int common_flag;
int RC_Mapped_Roll;
int RC_Mapped_Pitch;

/////////////////////////////
////////MOTOR ESC///////////
////////////////////////////
#define FRONT 0
#define BACK  1
#define LEFT  2
#define RIGHT 3


int    ESC_MOTOR_OUTPUT[4] = {0, 0, 0, 0};
        
#define ESC_MOTOR_F_PIN    12
#define ESC_MOTOR_B_PIN    11
#define ESC_MOTOR_L_PIN    6
#define ESC_MOTOR_R_PIN    5

#define MINCOMMAND 1025
#define MAXCOMMAND 1950
#define MIN_ANGLE -45
#define MAX_ANGLE 45
////////////////////////////
////////IMU UNIT////////////
////////////////////////////
///////GYROSCOPE////////////
////////////////////////////
#define L3G4200D_ADDR 0x69

#define L3G4200D_WHO_AM_I 0x0F
#define L3G4200D_CTRL_REG1 0x20
#define L3G4200D_CTRL_REG2 0x21
#define L3G4200D_CTRL_REG3 0x22
#define L3G4200D_CTRL_REG4 0x23
#define L3G4200D_CTRL_REG5 0x24

#define L3G4200D_OUT_X_L 0x28
#define L3G4200D_OUT_X_H 0x29
#define L3G4200D_OUT_Y_L 0x2A
#define L3G4200D_OUT_Y_H 0x2B
#define L3G4200D_OUT_Z_L 0x2C
#define L3G4200D_OUT_Z_H 0x2D

#define L3G4200D_STATUS_REG 0x27 //Läs bit för bit (bit 8 = xyz) ifall det har kommit nya värden

int      L3G4200D_x,
         L3G4200D_y,
         L3G4200D_z;
float    L3G4200D_OFFSET_x,
         L3G4200D_OFFSET_y,
         L3G4200D_OFFSET_z;
float    L3G4200D_CALIB_x,
         L3G4200D_CALIB_y,
         L3G4200D_CALIB_z;
float    L3G4200D_DPS_x,
         L3G4200D_DPS_y,
         L3G4200D_DPS_z;
float    GYRO_pitch,
         GYRO_roll;     

///////////////////////////////////////
///////////ACCELEROMETER//////////////
/////////////////////////////////////

#define ADXL345_ADDR 0x53

#define ADXL345_WHO_AM_I       0x00      // Device ID. 
#define ADXL345_ACT_INACT_CTL  0x27      // Axis enable control for activity and inactivity detection. 
#define ADXL345_BW_RATE        0x2c      // Data rate and power mode control. 
#define ADXL345_POWER_CTL      0x2D      // Power-saving features control.
#define ADXL345_DATA_FORMAT    0x31      // Data format control.

#define ADXL345_OUT_X_L 0x32
#define ADXL345_OUT_X_H 0x33
#define ADXL345_OUT_Y_L 0x34
#define ADXL345_OUT_Y_H 0x35
#define ADXL345_OUT_Z_L 0x36
#define ADXL345_OUT_Z_H 0x37

int      ADXL345_x,
         ADXL345_y,
         ADXL345_z;
float    ADXL345_OFFSET_x,
         ADXL345_OFFSET_y,
         ADXL345_OFFSET_z;
float    ADXL345_CALIB_x,
         ADXL345_CALIB_y,
         ADXL345_CALIB_z;
float    ADXL345_G_x,
         ADXL345_G_y,
         ADXL345_G_z;
float    ACCEL_pitch,
         ACCEL_roll;
 
 
///////////////////////////////////////
///////////MAGNETOMETER///////////////
/////////////////////////////////////

#define HMC5883L_ADDR           0x1E

#define HMC5883L_REG_A          0x00
#define HMC5883L_REG_B          0x01
#define HMC5883L_MODE_REG       0x02

#define HMC5883L_X_MSB          0x03
#define HMC5883L_X_LSB          0x04
#define HMC5883L_Z_MSB          0x05
#define HMC5883L_Z_LSB          0x06
#define HMC5883L_Y_MSB          0x07
#define HMC5883L_Y_LSB          0x08

#define HMC5883L_STATUS_REG     0x09

///////////////////////////////////////
///////COMMON VARIABLES FOR IMU///////
/////////////////////////////////////         
float Complementary_pitch = 0,
      Complementary_roll = 0;
             
byte buffer[8];
uint32_t sensor_timer;
uint32_t last_timer;

byte DEV_ID;


///////////////////////////////////////
/////////////PID REGULATOR////////////
/////////////////////////////////////
float error_integral; // felet för Ki(intergraldelen)
float error_derivata; //felet för Kd(deriveringsdelen)
float error_prop;   // felet för Kp(proportionelladelen)
float sample_time=10;// sampletiden 10 ms
 
#define SETPOINT   0                   
#define P_INPUT    1
#define LAST_INPUT 2
#define P_OUTPUT   3
#define SETPOINT   4
#define KP         5
#define KI         6
#define KD         7

                   //INPUT, LAST_INPUT, OUTPUT, SETPOINT, KP, KI, KD)
double PID_ROLL[8]   = {0, 0, 0, 0, 0, 0.004, 0.008, 0.0};
double PID_PITCH[8]  = {0, 0, 0, 0, 0, 0.5, 0.0, 0.5};
float PID_YAW[8]    = {0, 0, 0, 0, 0, 0.5, 0.0, 0.5};

long time_last, time_actual;
int time_change;

