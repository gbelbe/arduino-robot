#include <Servo.h> // Include Servo Library
#include <NewPing.h> // Include Newping Library

// L298N Control Pins
const int LeftMotorForward = 9;
const int LeftMotorBackward = 8;
const int RightMotorForward = 7;
const int RightMotorBackward = 6;
const int LeftMotorOn = 10;
const int RightMotorOn = 5;
const int Sound = 2;

#define TRIGGER_PIN 13 // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN 12 // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 250 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 250cm.

Servo servo_motor; // Servo's name
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.
boolean goesForward = false;
int distance = 150;

void setup()
{

Serial.begin(9600);

// Set L298N Control Pins as Output
pinMode(RightMotorForward, OUTPUT);
pinMode(LeftMotorForward, OUTPUT);
pinMode(LeftMotorBackward, OUTPUT);
pinMode(RightMotorBackward, OUTPUT);
pinMode(LeftMotorOn, OUTPUT);
pinMode(RightMotorOn, OUTPUT);

pinMode(Sound, OUTPUT);
digitalWrite(Sound, HIGH);

servo_motor.attach(11); // Attachs the servo on pin 11 to servo object.
servo_motor.write(90); // Set at 90 degrees.
delay(500); // Wait for 500ms.
distance = readPing(); // Get Ping Distance.
Serial.print(distance);
delay(200); // Wait for 200ms.




}

void loop()
{
  
int distanceRight = 0;
int distanceLeft = 0;





if (distance <= 30)
{
  moveStop();
  delay(300);
  moveBackward();
  delay(400);
  moveStop();
  delay(200);
  distanceRight = lookRight();
  delay(200);
  distanceLeft = lookLeft();

  
  
  if (distanceRight >= distanceLeft)
    {
      turnRight();
      delay(275);
      moveStop();
      distance = readPing();
  
    }else{
      turnLeft();
      delay(275);
      moveStop();
      distance = readPing();
    }

}else{
  
moveForward();

}



distance = readPing();
}


int lookLeft() // Look Right Function for Servo Motor
{
servo_motor.write(180);
delay(500);
int distance = readPing();
//Serial.print(distance);
delay(500);
servo_motor.write(90);
return distance;
}

int lookRight() // Look Left Function for Servo Motor
{
servo_motor.write(0);
delay(500);
int distance = readPing();
//Serial.print(distance);
delay(500);
servo_motor.write(90);
return distance;
}

int readPing() // Read Ping Function for Ultrasonic Sensor.
{
delay(75); // Wait 100ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.
int cm = sonar.ping_cm(); //Send ping, get ping distance in centimeters (cm).
//Serial.print(cm);
if (cm==0)
{
cm=250;
}
return cm;
}

void moveStop() // Move Stop Function for Motor Driver.
{
digitalWrite(RightMotorForward, LOW);
digitalWrite(RightMotorBackward, LOW);
digitalWrite(LeftMotorForward, LOW);
digitalWrite(LeftMotorBackward, LOW);
digitalWrite(RightMotorOn, LOW);
digitalWrite(LeftMotorOn, LOW);

}

void moveForward() // Move Forward Function for Motor Driver.
{
digitalWrite(RightMotorForward, HIGH);
digitalWrite(RightMotorBackward, LOW);
digitalWrite(LeftMotorForward, HIGH);
digitalWrite(LeftMotorBackward, LOW);
digitalWrite(RightMotorOn, HIGH);
digitalWrite(LeftMotorOn, HIGH);
}

void moveBackward() // Move Backward Function for Motor Driver.
{
digitalWrite(RightMotorForward, LOW);
digitalWrite(RightMotorBackward, HIGH);
digitalWrite(LeftMotorForward, LOW);
digitalWrite(LeftMotorBackward, HIGH);
digitalWrite(RightMotorOn, HIGH);
digitalWrite(LeftMotorOn, HIGH);
}

//void turnRight()// Turn Right Function for Motor Driver.
void turnRight()
{
digitalWrite(RightMotorForward, LOW);
digitalWrite(RightMotorBackward, HIGH);
digitalWrite(LeftMotorForward, HIGH);
digitalWrite(LeftMotorBackward, LOW);
digitalWrite(RightMotorOn, HIGH);
digitalWrite(LeftMotorOn, HIGH);
}

//void turnLeft() // Turn Left Function for Motor Driver.
void turnLeft()
{
digitalWrite(RightMotorForward, HIGH);
digitalWrite(RightMotorBackward, LOW);
digitalWrite(LeftMotorForward, LOW);
digitalWrite(LeftMotorBackward, HIGH);
digitalWrite(RightMotorOn, HIGH);
digitalWrite(LeftMotorOn, HIGH);
}
