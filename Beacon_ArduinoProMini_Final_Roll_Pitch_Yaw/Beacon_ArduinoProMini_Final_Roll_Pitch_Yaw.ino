#include <FaBo9Axis_MPU9250.h>
#include <SoftwareSerial.h>
SoftwareSerial HM10(2, 3); // RX = 2, TX = 3
String msg = "";
float roll , pitch, yaw;
FaBo9Axis fabo_9axis;

void setup() {
  Serial.begin(9600);
  Serial.println("RESET");
  Serial.println();
  HM10.begin(9600);
  Serial.println("configuring device.");
  //HM10.print("configuring device.");
  if (fabo_9axis.begin()) {
    Serial.println("configured FaBo 9Axis I2C Brick");
    //HM10.print("configured FaBo 9Axis I2C Brick");
  }
  else {
    Serial.println("device error");
    //HM10.print("device error");
    while(1);
  }
}

void loop() {  

  float ax,ay,az;
  float gx,gy,gz;
  float mx,my,mz;
//  float temp;
  
  fabo_9axis.readAccelXYZ(&ax,&ay,&az);
  fabo_9axis.readGyroXYZ(&gx,&gy,&gz);
  fabo_9axis.readMagnetXYZ(&mx,&my,&mz);
//  fabo_9axis.readTemperature(&temp);

  pitch = atan2 (ay ,( sqrt ((ax * ax) + (az * az))));
  roll = atan2(-ax ,( sqrt((ay * ay) + (az * az))));

  // yaw from mag

  float Yh = (my * cos(roll)) - (mz * sin(roll));
  float Xh = (mx * cos(pitch))+(my * sin(roll)*sin(pitch)) + (mz * cos(roll) * sin(pitch));

  yaw =  atan2(Yh, Xh);
  
  msg += "a" + String(pitch, 2) + "x" + String(roll, 2) + "x" + String(yaw, 2) + "x";

  Serial.println(msg);
  HM10.print(msg);
  
  msg = "";

  delay(100);
}

