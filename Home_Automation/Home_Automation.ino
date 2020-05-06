#include <Servo.h>
Servo myservo;
String voice;
int
led1 = 2, //Connect LED 1 To Pin #2
led2 = 3, //Connect LED 2 To Pin #3
led3 = 4, //Connect LED 3 To Pin #4
led4 = 5, //Connect LED 4 To Pin #5
led5 = 11; //Connect LED 5 To Pin #6
int pirSensor = 8;
int relayInput = 7;
int smokeA0 = A3;
// Your threshold value
int sensorThres = 400;
// defines pins numbers
const int trigPin = 9;
const int echoPin = 10;
// defines variables
long duration;
int distance;
//--------------------------Call A Function-------------------------------// 
void allon(){
     digitalWrite(led1, HIGH);
     digitalWrite(led2, HIGH);
     digitalWrite(led3, HIGH);
     digitalWrite(led4, HIGH);
     digitalWrite(led5, HIGH);
}
void alloff(){
     digitalWrite(led1, LOW);
     digitalWrite(led2, LOW);
     digitalWrite(led3, LOW);
     digitalWrite(led4, LOW);
     digitalWrite(led5, LOW);
}
//-----------------------------------------------------------------------// 
void setup() {
  Serial.begin(9600);
  myservo.attach(6,600,2300);  // (pin, min, max)
  myservo.write(0);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  pinMode(led5, OUTPUT);
  pinMode(pirSensor, INPUT);
  pinMode(relayInput, OUTPUT);
  pinMode(smokeA0, INPUT);
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input 
}
//-----------------------------------------------------------------------// 
void loop() 
{
int sensorValue = digitalRead(pirSensor);
  if (sensorValue == 1) 
  {
    Serial.println(sensorValue);
    digitalWrite(relayInput,HIGH); // The Relay Input works Inversly
    //myservo.write(180);              
    delay(1500);
  }
  else
  {
    digitalWrite(relayInput,LOW);
    //myservo.write(0);  // tell servo to go to a particular angle
    delay(1000);
  }
   
 int analogSensor = analogRead(smokeA0);
  //Serial.print("Pin A0: ");
  Serial.println(analogSensor);
  // Checks if it has reached the threshold value
  delay(1000);
 if(analogSensor >= 400)
 {
  Serial.println("Fire Detected");
  delay(2000);
 }

// Clears the trigPin
digitalWrite(trigPin, LOW);
delayMicroseconds(2);
// Sets the trigPin on HIGH state for 10 micro seconds
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
// Reads the echoPin, returns the sound wave travel time in microseconds
duration = pulseIn(echoPin, HIGH);
// Calculating the distance
distance= duration*0.034/2;
// Prints the distance on the Serial Monitor
Serial.print("Distance: ");
Serial.println(distance);
delay(2000);
if(distance<=50)
{
  myservo.write(0);  // tell servo to go to a particular angle
  delay(1000);
  
  myservo.write(90);              
  delay(500); 
  
  myservo.write(135);              
  delay(500);
  
  myservo.write(180);              
  delay(1500);
}
  
  while (Serial.available()){  //Check if there is an available byte to read
  delay(10); //Delay added to make thing stable
  char c = Serial.read(); //Conduct a serial read
  if (c == '#') {break;} //Exit the loop when the # is detected after the word
  voice += c; //Shorthand for voice = voice + c
  } 
  if (voice.length() > 0) {
    Serial.println(voice);
//-----------------------------------------------------------------------//   
  //----------Control Multiple Pins/ LEDs----------// 
       if(voice == "*Sab on karo") {allon();}  //Turn Off All Pins (Call Function)
  else if(voice == "*Sab band karo"){alloff();} //Turn On  All Pins (Call Function)
 
  //----------Turn On One-By-One----------//
  else if(voice == "*TV on") {digitalWrite(led1, HIGH);}
  else if(voice == "*fan on") {digitalWrite(led2, HIGH);}
  else if(voice == "*computer on") {digitalWrite(led3, HIGH);}
  else if(voice == "*bedroom lights on") {digitalWrite(led4, HIGH);}
  else if(voice == "*bathroom lights on") {digitalWrite(led5, HIGH);}
  //----------Turn Off One-By-One----------//
  else if(voice == "*TV off") {digitalWrite(led1, LOW);}
  else if(voice == "*fan off") {digitalWrite(led2, LOW);}
  else if(voice == "*computer off") {digitalWrite(led3, LOW);}
  else if(voice == "*bedroom lights off") {digitalWrite(led4, LOW);}
  else if(voice == "*bathroom lights off") {digitalWrite(led5, LOW);}
//-----------------------------------------------------------------------// 
voice="";} //Reset the variable after initiating
}
