/*
  YostLabsI2C.h - Library for reading Yost Labs 3-Space IMU over I2C.
  Created by Kundan Panta, 2022.
  Released into the public domain.
*/

#ifndef YostLabsI2C_h
#define YostLabsI2C_h

#include "Arduino.h"
#include <Wire.h>

// Define I2C addresses
#define YOST_NANO_I2C_ADD 0x46

// Define I2C/SPI command codes
// Initiation
#define YOST_READ_STATUS 0x41
#define YOST_WRITE 0x42
#define YOST_READ 0x43

// Operation
#define TARED_QUAT 0x00
#define TARED_EULER 0x01
#define TARED_ROTMAT 0x02
#define UNTARED_QUAT 0x06
#define UNTARED_EULER 0x07
#define UNTARED_ROTMAT 0x08
#define TEMP_C 0x2b

// Configuration
#define AUTO_CAL_GYRO 0xa5
#define RESTORE_FACTORY 0xe0
#define COMMIT_CONFIG 0xe1
#define SET_STATE_MAG 0x6d
#define GET_STATE_MAG 0x8e
#define SET_AXES 0x74
#define GET_AXES 0x8f
#define SET_REF_VECTOR_MODE 0x69
#define GET_REF_VECTOR_MODE 0x87
#define SET_OVERSAMPLE 0x6a
#define GET_OVERSAMPLE 0x90
#define GET_UPDATE_RATE 0x84
#define SET_RUNNING_AVE 0x75
#define GET_RUNNING_AVE 0x91
#define SET_TARE_CURRENT 0x60
#define GET_TARE_QUAT 0x80
#define GET_TARE_ROTMAT 0x81

class Yost_3Space {
public:
  // Constructor to define what data is return with readOrientation() method.
  // orientationVar = pointer to array to be updated with the orientation values
  // orientationFormat = 0, 1 (default), 2
  //                   = quaternion, Euler angles (default), rotation matrix respectively
  // readTared = true (untared orientation) (default)
  //           = false (untared orientation)
  Yost_3Space(float *orientationVar, int8_t orientationFormat = 1, bool readTared = true);

  // Initialize and test I2C connection
  bool begin(TwoWire &wirePort = Wire);

  // Ask for status packet
  unsigned char readStatus(void);

  // Return the orientation in the format specified by the constructor
  void readOrientation(void);

  // Return the orientation as quaternion

  // Return the orientation in yaw-pitch-roll

  // Return the orientation as rotation matrix


private:
  float *_orientationVar;
  int8_t _orientationFormat;
  bool _readTared;
  TwoWire *_i2cPort;

  // Send TSS command to sensor with no additional arguments
  void i2cCmdNoArgs(uint8_t cmd);
  // void i2cCmd(uint8_t cmd, const unsigned char * args);

  // Prepare sensor to send data
  void i2cPrepareToSend(void);
};

#endif
