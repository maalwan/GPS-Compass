#include "I2Cdev.h"
#include "MPU6050_6Axis_MotionApps612.h"
#include <Wire.h>

// MPU connection details
#define mpuSDA 21
#define mpuSCL 22
MPU6050 mpu(0x68, &Wire1);

// MPU variables
uint8_t fifoBuffer[128];
Quaternion q;
float mpuOffset = 0;

// Get modified heading based on offset
float getMPUHeading(void) {
  float heading = getRawYaw();
  // Heading is arbitrary and must be corrected using offset 
  heading += mpuOffset;
  if (heading > 180) { return heading - 360; } 
  else if (heading < -180) { return heading + 360; }
  return heading;
}

// Calculate offset based on current heading
void zeroMPU(void) {
    mpuOffset = -getRawYaw();
}

// Based on original arbitrary "north" from calibration (values between -180 and 180)
float getRawYaw(void) {
  return atan2(2 * q.x * q.y - 2 * q.w * q.z, 
                2 * q.w * q.w + 2 * q.x * q.x - 1) * 180/M_PI;
}

// Call at startup, restart microcontroller if failure to connect
void MPUSetup(){
  Wire1.begin(mpuSDA, mpuSCL, (uint32_t)100000);
  mpu.initialize();
  
  if (mpu.testConnection() && !mpu.dmpInitialize()) {
    // Calibrate accelerameter (hold the device still)
    mpu.CalibrateAccel(6);
    mpu.CalibrateGyro(6);
    mpu.setDMPEnabled(true);;
  } else {
    // Something is wrong with the wiring
    //Serial.println("Initilization failed");
    delay(5000);
    ESP.restart();
  }
}

// Reads data from MPU dmp, store rotation as quaternion to be processed later
void MPULoop() {
  if (mpu.dmpGetCurrentFIFOPacket(fifoBuffer)) {
    mpu.dmpGetQuaternion(&q, fifoBuffer);
  }
}