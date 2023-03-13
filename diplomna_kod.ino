#include <dht.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_MPU6050.h>
#include <Keypad.h>

const byte ROWS = 4;
const byte COLS = 1;
const byte ROW_PINS[ROWS] = { 8, 9, 6, 7 };
const byte COL_PINS[COLS] = {1};
char keys[ROWS][COLS] = { '1', '2', '3', '4' };
Keypad keypad = Keypad(makeKeymap(keys), ROW_PINS, COL_PINS, ROWS, COLS);


dht DHT;
Adafruit_MPU6050 mpu;

#define DHT11_PIN 2
#define IN1_PIN 4 
#define IN2_PIN 5 


const int fanOnTemp = 18; 
const int fanOffTemp = 34; 
const float Kp = 5; 
const float Ki = 0.1; 
const float Kd = 0.5; 
const int setpoint = 36; 

int previousError = 0;
float integral = 0;



void setup(){
  pinMode(IN1_PIN, OUTPUT);
  pinMode(IN2_PIN, OUTPUT);
  digitalWrite(IN1_PIN, LOW);
  digitalWrite(IN2_PIN, LOW);

  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
  
  Serial.begin(9600);

}

void loop(){

  char key = keypad.getKey();
  if (key != NO_KEY){
    Serial.write(key);
  }
  
  {
  int chk = DHT.read11(DHT11_PIN);
  float temperature = DHT.temperature;
  Serial.print("Temperature = ");
  Serial.println(DHT.temperature);
  Serial.print("Humidity = ");
  Serial.println(DHT.humidity);
  Serial.println(" ");
  delay(1000);
  

  int error = setpoint - temperature;
  integral += error;
  float derivative = error - previousError;
  previousError = error;
  float pidOutput = Kp * error + Ki * integral + Kd * derivative;

  if (pidOutput > 0) {
    digitalWrite(IN1_PIN, pidOutput);
    digitalWrite(IN2_PIN, LOW);
  } else {
    digitalWrite(IN1_PIN, LOW);
    digitalWrite(IN2_PIN, -pidOutput);
  }


  if (temperature >= fanOnTemp) {
    digitalWrite(IN1_PIN, HIGH);
    digitalWrite(IN2_PIN, LOW);
  } else if (temperature <= fanOffTemp) {
    digitalWrite(IN1_PIN, LOW);
    digitalWrite(IN2_PIN, LOW);
  }
  }
  
  {
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  Serial.print("Acceleration X: ");
  Serial.print(a.acceleration.x);
  Serial.print(", Y: ");
  Serial.print(a.acceleration.y);
  Serial.print(", Z: ");
  Serial.print(a.acceleration.z);
  Serial.println(" ");

  Serial.print("Rotation X: ");
  Serial.print(g.gyro.x);
  Serial.print(", Y: ");
  Serial.print(g.gyro.y);
  Serial.print(", Z: ");
  Serial.print(g.gyro.z);
  Serial.println(" ");

  Serial.println("");
  delay(100);
  

  if ( a.acceleration.x = 0.23, a.acceleration.y = 0.05){
      digitalWrite(IN1_PIN, LOW);
      digitalWrite(IN2_PIN, LOW);
    }
  }
}
