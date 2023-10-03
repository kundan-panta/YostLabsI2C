#include <YostLabsI2C.h>

#define IMU_UPDATE_RATE 100.  // Hz
int dt = 1000. / IMU_UPDATE_RATE;  // ms
float imuEuler[3] = { 0., 0., 0. };  // Array to hold the Euler angles
Yost_3Space imu(imuEuler);

void setup() {
  Serial.begin(115200);
  Wire.begin();
  // Wire.setClock(400000);
  imu.begin();
  Serial.println("Yaw,Pitch,Roll");
}

void loop() {
  long t = millis();
  while (millis() - t <= dt);
  imu.readOrientation();
  Serial.print(imuEuler[0] * 180. / M_PI);
  Serial.print(",");
  Serial.print(imuEuler[1] * 180. / M_PI);
  Serial.print(",");
  Serial.print(imuEuler[2] * 180. / M_PI);
  Serial.print("\n");
}
