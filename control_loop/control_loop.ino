#include <Adafruit_MotorShield.h>

const int leftSensorPin = A0;
const int rightSensorPin = A1;
const int switchPin = 7;

int leftSensor = 0;
int rightSensor = 0;
int deviation = 0;
const float kp = 0.3; // 0.3 works with baseSpeed 25

const int baseSpeed = 25; // 25, 20 works with 0.3 k
int leftSpeed;
int rightSpeed;

// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield();

// Left motor 
Adafruit_DCMotor *leftMotor = AFMS.getMotor(1);
// Right motor 
Adafruit_DCMotor *rightMotor = AFMS.getMotor(3);

void setup() {
  Serial.begin(9600);           // set up Serial library at 9600 bps
  Serial.println("Adafruit Motorshield v2 - DC Motor test!");

  if (!AFMS.begin()) {         // create with the default frequency 1.6KHz
  // if (!AFMS.begin(1000)) {  // OR with a different frequency, say 1KHz
    Serial.println("Could not find Motor Shield. Check wiring.");
    while (1);
  }
  
  Serial.println("Motor Shield found.");
}

void loop() {
  if (digitalRead(switchPin) == LOW) {
    rightSpeed = 0;
    leftSpeed = 0;
  } else {
    // get sensor input
    leftSensor = analogRead(leftSensorPin);
    rightSensor = analogRead(rightSensorPin);
    
    //compute deviation
    deviation = rightSensor - leftSensor;

  
    if (abs(deviation) >= 10) {
      leftSpeed = baseSpeed + kp * deviation;
      rightSpeed = baseSpeed - kp * deviation;
      Serial.println(leftSpeed, rightSpeed); 
    } else {
      rightSpeed = baseSpeed;
      leftSpeed = baseSpeed;
    }
  }
  rightMotor->setSpeed(rightSpeed);
  rightMotor->run(BACKWARD);
  //rightMotor->run(RELEASE);

  leftMotor->setSpeed(leftSpeed);
  leftMotor->run(FORWARD);
  //leftMotor->run(RELEASE);
  delay(100);

}
