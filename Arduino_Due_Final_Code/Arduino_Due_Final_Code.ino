#include <Servo.h>
Servo radarServo;

int F = 0;
int R = 0;
int L = 0;
void setup()
{
  Serial.begin( 115200);   // Intialize terminal serial port
    delay(20);               // Give port time to initalize
    Serial2.begin( 115200);  // Initialize TFMPLus device serial port.
    delay(20);               // Give port time to initalize
  radarServo.attach(5);
  pinMode(2, INPUT);
  pinMode(3, INPUT);
  pinMode(4, INPUT);
  
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
}
void getTFminiData(int* distance, int* strength) {
  static char i = 0;
  char j = 0;
  int checksum = 0; 
  static int rx[9];
  if(Serial2.available())
  {  
    // Serial.println( "tfmini serial available" );
    rx[i] = Serial2.read();
    if(rx[0] != 0x59) {
      i = 0;
    } else if(i == 1 && rx[1] != 0x59) {
      i = 0;
    } else if(i == 8) {
      for(j = 0; j < 8; j++) {
        checksum += rx[j];
      }
      if(rx[8] == (checksum % 256)) {
        *distance = rx[2] + rx[3] * 256;
        *strength = rx[4] + rx[5] * 256;
      }
      i = 0;
    } else 
    {
      i++;
    } 
  }  
}

void loop() 
{
  int distance = 0;
  int strength = 0;

  F = digitalRead(2);
  R = digitalRead(3);
  L = digitalRead(4);
  
  for(int i=0;i<=180;i=i+2)
  {
        digitalWrite(6, HIGH);
        digitalWrite(7, LOW);
        digitalWrite(8, HIGH);
        digitalWrite(9, LOW);
    radarServo.write(i);
    delay(1);
    distance = 0;
    strength = 0;

    getTFminiData(&distance, &strength);
    while(!distance) {
    getTFminiData(&distance, &strength);
    if(distance) {
      Serial.print(distance);
      Serial.print("cm\t");
      Serial.print("strength: ");
      Serial.println(strength);
      if (distance <=35){
        if (i < 60){
          Serial.print("Right Obstacle");
          digitalWrite(6, LOW);
          digitalWrite(7, HIGH);
          digitalWrite(8, HIGH);
          digitalWrite(9, LOW);
          }
        else if (i > 120){
          Serial.print("Left Obstacle");
          digitalWrite(6, HIGH);
          digitalWrite(7, LOW);
          digitalWrite(8, LOW);
          digitalWrite(9, HIGH);
          }
        else{
          digitalWrite(6, LOW);
          digitalWrite(7, LOW);
          digitalWrite(8, LOW);
          digitalWrite(9, LOW);
          Serial.print("Stop Front Obstacle");
          }
        while(distance <=35){
          getTFminiData(&distance, &strength);
          }
        
      }

      else if(F){
        digitalWrite(6, HIGH);
        digitalWrite(7, LOW);
        digitalWrite(8, HIGH);
        digitalWrite(9, LOW);
        Serial.print("\nForward\n");  
      }
      else if(R){
        digitalWrite(6, HIGH);
        digitalWrite(7, LOW);
        digitalWrite(8, LOW);
        digitalWrite(9, HIGH);
        Serial.print("\nRight\n");  
      }
      else if(L){
        digitalWrite(6, LOW);
        digitalWrite(7, HIGH);
        digitalWrite(8, HIGH);
        digitalWrite(9, LOW);
        Serial.print("\nLeft\n");  
      }
      else{
        digitalWrite(6, LOW);
        digitalWrite(7, LOW);
        digitalWrite(8, LOW);
        digitalWrite(9, LOW);
        Serial.print("Stop Front Obstacle");
        }
     // delay(30);
  }
  }
  }
  for(int i=180;i>=0;i=i-2)
  {
        digitalWrite(6, HIGH);
        digitalWrite(7, LOW);
        digitalWrite(8, HIGH);
        digitalWrite(9, LOW);
    radarServo.write(i);
    delay(1);
   int distance = 0;
  int strength = 0;

  getTFminiData(&distance, &strength);
  while(!distance) {
    getTFminiData(&distance, &strength);
    if(distance) {
      Serial.print(distance);
      Serial.print("cm\t");
      Serial.print("strength: ");
      Serial.println(strength);
      if (distance <= 35){
        if (i < 60){
          Serial.print("Right Obstacle");
          digitalWrite(6, LOW);
          digitalWrite(7, HIGH);
          digitalWrite(8, HIGH);
          digitalWrite(9, LOW);
          }
        else if (i > 120){
          Serial.print("Left Obstacle");
          digitalWrite(6, HIGH);
          digitalWrite(7, LOW);
          digitalWrite(8, LOW);
          digitalWrite(9, HIGH);
          }
        else{
          digitalWrite(6, LOW);
          digitalWrite(7, LOW);
          digitalWrite(8, LOW);
          digitalWrite(9, LOW);
          Serial.print("Stop Front Obstacle");
          }
        while(distance <=35){
          getTFminiData(&distance, &strength);
          }

      else if(F){
        digitalWrite(6, HIGH);
        digitalWrite(7, LOW);
        digitalWrite(8, HIGH);
        digitalWrite(9, LOW);
        Serial.print("\nForward\n");  
      }
      else if(R){
        digitalWrite(6, HIGH);
        digitalWrite(7, LOW);
        digitalWrite(8, LOW);
        digitalWrite(9, HIGH);
        Serial.print("\nRight\n");  
      }
      else if(L){
        digitalWrite(6, LOW);
        digitalWrite(7, HIGH);
        digitalWrite(8, HIGH);
        digitalWrite(9, LOW);
        Serial.print("\nLeft\n");  
      }
      else{
        digitalWrite(6, LOW);
        digitalWrite(7, LOW);
        digitalWrite(8, LOW);
        digitalWrite(9, LOW);
        Serial.print("Stop Front Obstacle");
        }
      }
     // delay(30);
  }
}
}
  }
