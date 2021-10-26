#include <Arduino.h>
#include <runtimer.h>

//Pins
const int lightSensor = A0; //Light sensor
const int ledPin = 10; //LED

//Variables
int lightValue = 0;
int sensorMax = 1023; //Max
int sensorMin = 0; //Min

// intervalTimer writeOutputTimer(400);
// intervalTimer readInputTimer(100);
intervalTimer displayValuesTimer(500);

void setup() 
{
  //Serial monitor
  Serial.begin(9600); 
  
  pinMode(ledPin, OUTPUT); 
  digitalWrite(ledPin, HIGH); //Turn led on at start (Turn light on at min light)

  while (millis() < 5000) 
  {
    lightValue = analogRead(lightSensor); //Get value of light intensity

    //Get max light intensity
    if (lightValue < sensorMax) 
    {
      sensorMax = lightValue;
    }

    //Get min light intensity
    if (sensorMin < lightValue)
    {
      sensorMin = lightValue;
    }
  }

  //Turn light off at max light
  digitalWrite(ledPin, LOW);
}

void loop() 
{
  //Get light intensity
  lightValue = analogRead(lightSensor);

  if (displayValuesTimer.expired())
  {
      Serial.println(lightValue);
  }

  //Map reading
  lightValue = map(lightValue, sensorMin, sensorMax, 0, 255);

  //Fix issue with its max range (Led kept resetting when it reached 255 and we don't want that)
  lightValue = constrain(lightValue, 0, 255);

  //Fade the light based on the light intensity
  analogWrite(ledPin, lightValue);
}