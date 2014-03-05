//Written by Ben Woodcock
#include <Servo.h> // references inbuilt arduino library 
const int tempsensorPin = A1;
const float baselineTemp = 32.0; //This sets the base line temperature at 32 degrees
const int lightSensorPin = A0;
const int pingPin = 13;
const int motorPin1 = 9;
const int motorPin2 = 8;
Servo myservo;
int Fan = 3; 
int lightSensorValue = 0;
int InfraredLed = 12;
int inPin = 11;
int safeZone = 30;
int LEDpins1= 1;
int LEDpins2= 2;
int LEDlights1 = 4;
int LEDlights2 = 5;

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
 }

void loop(){
  for(int i=0;i<15;i++){ // This for loop controls the led's blinking i have made this loop go round 15 times because the raspberry pi takes time to boot 
    digitalWrite(LEDpins1, HIGH);
    delay(1000);
    digitalWrite(LEDpins1, LOW);
  }
  for(int i=0;i<15;i++){// This for loop controls the final led's blinking that will give the indication that the raspberry pi is nearly booted 
    digitalWrite(LEDpins2,HIGH);
    delay(1000);
    digitalWrite(LEDpins2,LOW);
  }
  
  lightSensorValue = analogRead(lightSensorPin);
  delay(1000);
  if(lightSensorValue<780)                // reads data from light sensor - if value is less than 780, switch on the Infrared LED
                                          // if more than 780, the infrared light remains off
  { 
    digitalWrite(InfraredLed, HIGH);
  }
  else if (lightSensorValue >780 && lightSensorValue <850) // however if the light sensor reads a value that is between 780 and 850 then two LED lights come on
  {
   digitalWrite(LEDlights1,HIGH);
   digitalWrite(LEDlights2,HIGH); 
  }
  else // but if the value is above 850 then both the LED's and the Infrared leds remain off
  {
    digitalWrite(LEDlights1,LOW);
    digitalWrite(LEDlights2,LOW);
    digitalWrite(InfraredLed,LOW);
  }
  
  long duration, cm;

  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);              
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(pingPin, LOW);
  
  
  duration = pulseIn(inPin, HIGH);
  
  cm = microsecondsToCentimeters(duration);
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();
  
  if (cm > safeZone)
  {
  digitalWrite(motorPin1, HIGH);
  digitalWrite(motorPin2, HIGH); 
  }
  else
  {
    myservo.write(0);
  }
  delay(100);

  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);            // sends out signal from ultrasonic sensor - if more than safezone value, turn motor 1 on - if less than safezone value, the servo head turns 170 degrees (turns the other way)
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(pingPin, LOW);
  

  duration = pulseIn(inPin, HIGH);
  
  cm = microsecondsToCentimeters(duration);
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();
  
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
  Serial.print("cm");                                         // calculations
  Serial.println();
  
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
