#include "Arduino.h"
#include "YostLabsI2C.h"

Yost_3Space::Yost_3Space(float *orientationVar, int8_t orientationFormat, bool readTared) {
  _orientationVar = orientationVar;
  _orientationFormat = orientationFormat;
  _readTared = readTared;
}

bool Yost_3Space::begin(TwoWire &wirePort) {
  _i2cPort = &wirePort;

  _i2cPort->beginTransmission(YOST_NANO_I2C_ADD);
  uint8_t error = _i2cPort->endTransmission();

  if (error == 0) return true;
  else return false;
}

unsigned char Yost_3Space::readStatus(void) {
  _i2cPort->beginTransmission(YOST_NANO_I2C_ADD);
  _i2cPort->write(YOST_READ_STATUS);
  _i2cPort->endTransmission();

  _i2cPort->requestFrom(YOST_NANO_I2C_ADD, 1);

  // Convert byte into float:
  unsigned char status = _i2cPort->read();
  return status;
}

void Yost_3Space::i2cCmdNoArgs(uint8_t cmd) {
  // Send command to sensor
  _i2cPort->beginTransmission(YOST_NANO_I2C_ADD);
  _i2cPort->write(YOST_WRITE);
  _i2cPort->write(cmd);
  _i2cPort->endTransmission();
}

void Yost_3Space::i2cPrepareToSend(void) {
  _i2cPort->beginTransmission(YOST_NANO_I2C_ADD);
  _i2cPort->write(YOST_READ);
  _i2cPort->endTransmission();
}

void Yost_3Space::readOrientation(void) {
  i2cCmdNoArgs(TARED_EULER);
  i2cPrepareToSend();

  // Request data from sensor
  const int dataLen = 12;
  _i2cPort->requestFrom(YOST_NANO_I2C_ADD, dataLen);

  // Collect requested data from sensors
  if (_i2cPort->available() >= dataLen) {
    // Convert 4 bytes for each of the three Euler angles into float
    for (int j = 0; j < 3; j++) {

      // Approach 1
      union byte2float {
        byte buffer[4];
        float reading;
      } value;
      // Convert 4 bytes into float:
      for (int i = 3; i >= 0; i--) {
        value.buffer[i] = _i2cPort->read();
      }
      *(_orientationVar + j) = value.reading;


      // Approach 2
      // unsigned char reading = 0;
      // float angle;
      // // Convert 4 bytes into float:
      // for (int i = 3; i >= 0; i--) {
      //   reading = _i2cPort->read();
      //   angle = reading << (8 * i);
      // }
      // *(_orientationVar + j) = angle;
    }
  }
}
