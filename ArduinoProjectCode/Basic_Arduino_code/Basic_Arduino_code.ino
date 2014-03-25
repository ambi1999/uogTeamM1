/*An Automated Robot controlled via a web-site hosted by the Raspberry Pi.
The Raspberry Pi is connected to the Arduino and the Arduino powers the robot.
We are Using a model B Pi and an Arduino MEGA 2560

All code must be commented and code must compile before being commited!

Code Written by: Ben Woodcock
Edited By: Ryan Maycroft, Ashley Hathaway,and Sava Minev
Copyright PiBot Group
*/
#define echoPin 7 // Echo Pin
#define trigPin 8 // Trigger Pin
#define LEDPin 13 // Onboard LED
#include <Servo.h> // references inbuilt arduino library 
const int tempsensorPin = A1;// this line states that the temperature sensor data will be coming in on the analog port 1
const float baselineTemp = 20.0; //This sets the base line temperature at 32 degrees
const int lightSensorPin = A0; // this line states that the light sensor data will be coming in on the analog port 0 
int maximumRange = 200; // Maximum range needed
int minimumRange = 0; // Minimum range needed
long duration, distance; // Duration used to calculate distance
const int motorPin1 = 9;//these lines of code set what pins are being used and by naming them it makes it easier to change
const int motorPin2 = 8;//these lines of code set what pins are being used and by naming them it makes it easier to change
Servo myservo;
int Fan = 3; //these lines of code set what pins are being used and by naming them it makes it easier to change
int lightSensorValue = 0; // This sets the light sensor value to 0 when starting 
int InfraredLed = 12;//these lines of code set what pins are being used and by naming them it makes it easier to change
int safeZone = 30; // this states that anywhere from 0 to 30 is the safezone
int LEDpins1= 1;//these lines of code set what pins are being used and by naming them it makes it easier to change
int LEDpins2= 2;//these lines of code set what pins are being used and by naming them it makes it easier to change
int LEDlights1 = 4;//these lines of code set what pins are being used and by naming them it makes it easier to change
int LEDlights2 = 5;//these lines of code set what pins are being used and by naming them it makes it easier to change
int temperature;


void tempRead () {
   int sensorVal = analogRead(tempsensorPin);
 
   //sensorVal=160;
  Serial.println(sensorVal);
  float temperature = sensorVal; 
  temperature = (temperature*5.0*100.0) /1240.0;
}

void motorTurnRight (){
digitalWrite(motorPin1, HIGH);
   digitalWrite(motorPin2, LOW);
   delay(1000);
   }

void setup(){
 Serial.begin(9600); 
 pinMode(trigPin, OUTPUT);
 pinMode(echoPin, INPUT);
 pinMode(LEDPin, OUTPUT);
 pinMode(LEDpins1, OUTPUT); // These lines define what pins are outputs and what pins are inputs so when you digitalWrite something to the pins they know if they are recieving or sending
 pinMode(LEDpins2, OUTPUT);// These lines define what pins are outputs and what pins are inputs so when you digitalWrite something to the pins they know if they are recieving or sending 
 pinMode(Fan, OUTPUT);// These lines define what pins are outputs and what pins are inputs so when you digitalWrite something to the pins they know if they are recieving or sending 
 pinMode(motorPin1, OUTPUT);// These lines define what pins are outputs and what pins are inputs so when you digitalWrite something to the pins they know if they are recieving or sending 
 pinMode(motorPin2, OUTPUT);// These lines define what pins are outputs and what pins are inputs so when you digitalWrite something to the pins they know if they are recieving or sending 
 pinMode(InfraredLed, OUTPUT);// These lines define what pins are outputs and what pins are inputs so when you digitalWrite something to the pins they know if they are recieving or sending 

 pinMode(LEDlights1, OUTPUT);// These lines define what pins are outputs and what pins are inputs so when you digitalWrite something to the pins they know if they are recieving or sending 
 pinMode(LEDlights2, OUTPUT);// These lines define what pins are outputs and what pins are inputs so when you digitalWrite something to the pins they know if they are recieving or sending 

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

  digitalWrite(trigPin, LOW); 
 delayMicroseconds(2); 

 digitalWrite(trigPin, HIGH);
 delayMicroseconds(10); 
 
 digitalWrite(trigPin, LOW);
 duration = pulseIn(echoPin, HIGH);
 
 //Calculate the distance (in cm) based on the speed of sound.
 distance = duration/58.2;
  
  
 
  

  Serial.print(distance);
  Serial.print("distance"); // this section converts how long it took the ping to come back and then  multiplys that value to the speed it was sent out by and thats the calculation for distance 
  Serial.println(); // then it takes the value and puts cm on it to make it a distance value
  
  if (distance > safeZone) // if the distance is greater than the safezone (30cm) then the two motors will be high making the robot move forward
  {
  digitalWrite(motorPin1, HIGH);
  digitalWrite(motorPin2, HIGH); 
  }
  else // however if the distance is shorter than the safezone then the servo motor will turn to 0 degrees
  {
    myservo.write(0);
  }
  delay(1000);

   digitalWrite(trigPin, LOW); 
 delayMicroseconds(2); 

 digitalWrite(trigPin, HIGH);
 delayMicroseconds(10); 
 
 digitalWrite(trigPin, LOW);
 duration = pulseIn(echoPin, HIGH);
 
 //Calculate the distance (in cm) based on the speed of sound.
 distance = duration/58.2;
  
  
 
  

  Serial.print(distance);
  Serial.print("distance"); // this section converts how long it took the ping to come back and then  multiplys that value to the speed it was sent out by and thats the calculation for distance 
  Serial.println(); // then it takes the value and puts cm on it to make it a distance value
  
  if (distance > safeZone)
  {
   int motorTurnRight ();
  }
  else
  {
   myservo.write(170);
  }
  delay(100);

   digitalWrite(trigPin, LOW); 
 delayMicroseconds(2); 

 digitalWrite(trigPin, HIGH);
 delayMicroseconds(10); 
 
 digitalWrite(trigPin, LOW);
 duration = pulseIn(echoPin, HIGH);
 
 //Calculate the distance (in cm) based on the speed of sound.
 distance = duration/58.2;
  
  
 
  

  Serial.print(distance);
  Serial.print("distance"); // this section converts how long it took the ping to come back and then  multiplys that value to the speed it was sent out by and thats the calculation for distance 
  Serial.println(); // then it takes the value and puts cm on it to make it a distance value
  
  if (distance > safeZone)
  {
   int motorTurnRight ();
  }
  else
  {
    myservo.write(90);
  }
  
  int tempRead;
 
delay(2000);
 
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
