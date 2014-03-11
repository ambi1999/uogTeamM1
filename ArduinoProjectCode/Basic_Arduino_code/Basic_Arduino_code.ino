/*An Automated Robot controlled via a web-site hosted by the Raspberry Pi.
The Raspberry Pi is connected to the Arduino and the Arduino powers the robot.
We are Using a model B Pi and an Arduino MEGA 2560

All code must be commented and code must compile before being commited!

Code Written by: Ben Woodcock
Edited By: Ashley Hathaway and Ryan Maycroft
Copyright PiBot Group
*/

#include <Servo.h> // references inbuilt arduino library 
const int tempsensorPin = A1;// this line states that the temperature sensor data will be coming in on the analog port 1
const float baselineTemp = 32.0; //This sets the base line temperature at 32 degrees
const int lightSensorPin = A0; // this line states that the light sensor data will be coming in on the analog port 0 
const int pingPin = 13; //these lines of code set what pins are being used and by naming them it makes it easier to change 
const int motorPin1 = 9;//these lines of code set what pins are being used and by naming them it makes it easier to change
const int motorPin2 = 8;//these lines of code set what pins are being used and by naming them it makes it easier to change
Servo myservo;
int Fan = 3; //these lines of code set what pins are being used and by naming them it makes it easier to change
int lightSensorValue = 0; // This sets the light sensor value to 0 when starting 
int InfraredLed = 12;//these lines of code set what pins are being used and by naming them it makes it easier to change
int inPin = 11;//these lines of code set what pins are being used and by naming them it makes it easier to change
int safeZone = 30; // this states that anywhere from 0 to 30 is the safezone
int LEDpins1= 1;//these lines of code set what pins are being used and by naming them it makes it easier to change
int LEDpins2= 2;//these lines of code set what pins are being used and by naming them it makes it easier to change
int LEDlights1 = 4;//these lines of code set what pins are being used and by naming them it makes it easier to change
int LEDlights2 = 5;//these lines of code set what pins are being used and by naming them it makes it easier to change

void setup(){
 Serial.begin(9600); 
 myservo.attach(7); // This is stating what pin the servo motor is attached to
 myservo.write(90); // This makes the default angle of the servo motor 90 degrees 
 pinMode(LEDpins1, OUTPUT); // These lines define what pins are outputs and what pins are inputs so when you digitalWrite something to the pins they know if they are recieving or sending
 pinMode(LEDpins2, OUTPUT);// These lines define what pins are outputs and what pins are inputs so when you digitalWrite something to the pins they know if they are recieving or sending 
 pinMode(Fan, OUTPUT);// These lines define what pins are outputs and what pins are inputs so when you digitalWrite something to the pins they know if they are recieving or sending 
 pinMode(motorPin1, OUTPUT);// These lines define what pins are outputs and what pins are inputs so when you digitalWrite something to the pins they know if they are recieving or sending 
 pinMode(motorPin2, OUTPUT);// These lines define what pins are outputs and what pins are inputs so when you digitalWrite something to the pins they know if they are recieving or sending 
 pinMode(InfraredLed, OUTPUT);// These lines define what pins are outputs and what pins are inputs so when you digitalWrite something to the pins they know if they are recieving or sending 
 pinMode(pingPin, OUTPUT);// These lines define what pins are outputs and what pins are inputs so when you digitalWrite something to the pins they know if they are recieving or sending 
 pinMode(LEDlights1, OUTPUT);// These lines define what pins are outputs and what pins are inputs so when you digitalWrite something to the pins they know if they are recieving or sending 
 pinMode(LEDlights2, OUTPUT);// These lines define what pins are outputs and what pins are inputs so when you digitalWrite something to the pins they know if they are recieving or sending 
 pinMode(inPin, INPUT);// These lines define what pins are outputs and what pins are inputs so when you digitalWrite something to the pins they know if they are recieving or sending 
 pinMode(tempsensorPin, INPUT);// These lines define what pins are outputs and what pins are inputs so when you digitalWrite something to the pins they know if they are recieving or sending 
 pinMode(lightSensorPin, INPUT);// These lines define what pins are outputs and what pins are inputs so when you digitalWrite something to the pins they know if they are recieving or sending 
    for(int i=0;i<15;i++){ // This for loop controls the led's blinking i have made this loop go round 15 times because the raspberry pi takes time to boot 
    digitalWrite(LEDpins1, HIGH);
    delay(500);
    digitalWrite(LEDpins1, LOW);
    delay(500);
  }
  for(int i=0;i<15;i++){// This for loop controls the final led's blinking that will give the indication that the raspberry pi is nearly booted 
    digitalWrite(LEDpins2,HIGH);
    delay(500);
    digitalWrite(LEDpins2,LOW);
    delay(500);
  }
  digitalWrite(LEDpins2,HIGH);
}

void loop(){

 
   lightSensorValue = analogRead(lightSensorPin);
  delay(1000);
  Serial.print("Photo Resistor Value: ");
  Serial.print(lightSensorValue);
  Serial.println();
  if(lightSensorValue<780)                // reads data from light sensor - if value is less than 780, switch on the Infrared LED
                                          // if more than 780, the infrared light remains off
  { 
    
  digitalWrite(InfraredLed, HIGH);

  }
  else if (lightSensorValue >780 && lightSensorValue <1000) // however if the light sensor reads a value that is between 780 and 850 then two LED lights come on
  {
   digitalWrite(LEDlights1,HIGH);
  }
  else 
  {
    digitalWrite(LEDlights1,LOW);
    
  }

  long duration, cm;

  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);              
  digitalWrite(pingPin, HIGH);// this part of code sends out a ping to measure the distance from the ultrasonic sensor
  delayMicroseconds(5);
  digitalWrite(pingPin, LOW);
  
  
  duration = pulseIn(inPin, HIGH);// this line waits for the ping to come back to the sensor and also times how long it took the ping to come back
  
  cm = microsecondsToCentimeters(duration);
  Serial.print(cm);
  Serial.print("cm"); // this section converts how long it took the ping to come back and then  multiplys that value to the speed it was sent out by and thats the calculation for distance 
  Serial.println(); // then it takes the value and puts cm on it to make it a distance value
  
  if (cm > safeZone) // if the distance is greater than the safezone (30cm) then the two motors will be high making the robot move forward
  {
  digitalWrite(motorPin1, HIGH);
  digitalWrite(motorPin2, HIGH); 
  }
  else // however if the distance is shorter than the safezone then the servo motor will turn to 0 degrees
  {
    myservo.write(0);
  }
  delay(1000);

  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);            
  digitalWrite(pingPin, HIGH);// sends out signal from ultrasonic sensor - if more than safezone value, turn motor 1 on - if less than safezone value, the servo head turns 170 degrees (turns the other way)
  delayMicroseconds(5);
  digitalWrite(pingPin, LOW);
  

  duration = pulseIn(inPin, HIGH);
  
  cm = microsecondsToCentimeters(duration);
  Serial.print(cm);
  Serial.print("cm");// this section converts how long it took the ping to come back and then  multiplys that value to the speed it was sent out by and thats the calculation for distance 
  Serial.println();// then it takes the value and puts cm on it to make it a distance value
  
  if (cm > safeZone)
  {
   digitalWrite(motorPin1, HIGH);
   digitalWrite(motorPin2, LOW);
   delay(1000);
  }
  else
  {
   myservo.write(170);
  }
  delay(100);

  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(pingPin, LOW);
  

  duration = pulseIn(inPin, HIGH);
  
  cm = microsecondsToCentimeters(duration);
  Serial.print(cm);
  Serial.print("cm");   // this section converts how long it took the ping to come back and then  multiplys that value to the speed it was sent out by and thats the calculation for distance 
  Serial.println();// then it takes the value and puts cm on it to make it a distance value
  
  if (cm > safeZone)
  {
   digitalWrite(motorPin1, LOW);
   digitalWrite(motorPin2, HIGH);
   delay(1000);
  }
  else
  {
    myservo.write(90);
  }
  
  int sensorVal = analogRead(tempsensorPin);
  Serial.print(sensorVal);
  float voltage = (sensorVal/1024.0) * 5.0;                      // if temperature value higher than baseline (32 degree c) switch on fan .. if less than baseline, keep fan off
  Serial.print(voltage);
  float temperature = (voltage - .5) * 100;
  Serial.println(temperature);
  
  if(temperature > baselineTemp)
  {
    digitalWrite(Fan, HIGH);
  }
  else
  {
    digitalWrite(Fan, LOW);
  }
  
}

long microsecondsToCentimeters(long microseconds)
{
  return microseconds / 29 / 2;
}
