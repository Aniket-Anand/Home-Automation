/*     Arduini PIR Motion Sensor Tutorial
 *      
 *  by Dejan Nedelkovski, www.HowToMechatronics.com
 *  
 */
int pirSensor = 11;
int relayInput = 7;
void setup() {
  pinMode(pirSensor, INPUT);
  pinMode(relayInput, OUTPUT); 
  Serial.begin(9600); 
}
void loop() {
  int sensorValue = digitalRead(pirSensor);
  if (sensorValue == 1) 
  {
    Serial.println(sensorValue);
    digitalWrite(relayInput,HIGH); // The Relay Input works Inversly
  }
  else
  {
    digitalWrite(relayInput,LOW);
  }
}
