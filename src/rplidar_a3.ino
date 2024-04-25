#include <RPLidar.h>

RPLidar lidar;

#define RPLIDAR_MOTOR \
  3  // The PWM pin for control the speed of RPLIDAR's motor

void setup() {
  lidar.begin(Serial1);
  pinMode(RPLIDAR_MOTOR, OUTPUT);
  delay(1000);

  Serial.begin(256000);
  Serial.println("Serial initialized.");
}
void loop() {
  if (IS_OK(lidar.waitPoint())) {
    float distance =
        lidar.getCurrentPoint().distance;
    float angle = lidar.getCurrentPoint().angle;

    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.print(" mm, Angle: ");
    Serial.print(angle);
    Serial.println(" degrees");

    bool startBit =
        lidar.getCurrentPoint()
            .startBit;
    byte quality =
        lidar.getCurrentPoint().quality;

  } else {
    analogWrite(RPLIDAR_MOTOR, 0);

    rplidar_response_device_info_t info;
    if (IS_OK(lidar.getDeviceInfo(info, 100))) {
      // Lidar detected
      lidar.startScan();
      Serial.println("Starting scan.");

      analogWrite(RPLIDAR_MOTOR, 255);
      delay(1000);
    }
  }
}