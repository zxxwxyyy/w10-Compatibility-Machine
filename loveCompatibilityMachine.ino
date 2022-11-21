// ----- Creative Coding Week 10 - Love Compatbility Machine
// ----- Liqian Zhang
// ----- reference: DHT Sensor Library by Adafruit 
// ----- reference: https://create.arduino.cc/projecthub/godboi123/love-o-meter-bda552
// ----- For this week's assignment, I decide to use DHT 11 temperature sensor to create a love compatbility machine. 
// ----- Just as people always say, if you meet the one you love, your heartbeat goes faster, your body temperature goes higher. 
// ----- I set up 4 lights on their individual circuits. Each light will light up when temperature rise up to a certain level. 


// DHT Temperature & Humidity Sensor
// Unified Sensor Library Example
// Written by Tony DiCola for Adafruit Industries
// Released under an MIT license.

// REQUIRES the following Arduino libraries:
// - DHT Sensor Library: https://github.com/adafruit/DHT-sensor-library
// - Adafruit Unified Sensor Lib: https://github.com/adafruit/Adafruit_Sensor

#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

#define DHTPIN 14     // ----- using digital pin 14 to get input value of the current temperature

#define DHTTYPE    DHT11     // DHT 11

DHT_Unified dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  // Initialize device.
  dht.begin();

// ----- detect output pin for the lights from 15-18, using forloop to save space, reference from: https://create.arduino.cc/projecthub/godboi123/love-o-meter-bda552;
  for(int pinOutput = 15; pinOutput<20; pinOutput++){
    pinMode(pinOutput, OUTPUT);
    digitalWrite(pinOutput, LOW);
  }

}

void loop() {
 // ----- loop runs every 0.5 seconds. 
  delay(500);
  // Get temperature event and print its value.
  // ----- using Adafruit example from the libraries to print out current temperature value.
  sensors_event_t event;
  dht.temperature().getEvent(&event);

    Serial.print(F("Temperature: "));
    Serial.print(event.temperature);
    Serial.println(F("°C"));

// ----- using if statement to control the light in different temperature situation. 
// ----- I run the sketch once and get that the current temperature of my room is 22°C, so I use it as the basic temperature of my function.
// ----- if the temperature keep goes up, I use the forloop for the breath effect from my last week assignment to analyze that the temperature is going up. 
  if(event.temperature <= 22){

    for(int i = 0; i <= 255; i++){
      analogWrite(15, i);
      delay(10);
    }
    for(int i = 255; i >= 0; i--){
      analogWrite(15, i);
      delay(10);
    }
    digitalWrite(16, LOW);
    digitalWrite(17, LOW);
    digitalWrite(19, LOW);
  }
  else if(event.temperature >= 22 && event.temperature < 23){
    // ----- I have had issue here because I didn't set the analogWrite back to 255. When the next light goes on, the previous light will be off. 
    // ----- I have to set analogWrite back to 255, because my previous for loop set it to 0. 
    digitalWrite(15, HIGH);
    analogWrite(15, 255);

    for(int i = 0; i <= 255; i++){
      analogWrite(16, i);
      delay(10);
    }
    for(int i = 255; i >= 0; i--){
      analogWrite(16, i);
      delay(10);
    }
    digitalWrite(17, LOW);
    digitalWrite(19, LOW);
  }
  else if(event.temperature >= 23 && event.temperature < 24){
    digitalWrite(15, HIGH);
    digitalWrite(16, HIGH);
    analogWrite(16, 255);

    for(int i = 0; i <= 255; i++){
      analogWrite(17, i);
      delay(10);
    }
    for(int i = 255; i >= 0; i--){
      analogWrite(17, i);
      delay(10);
    }
    digitalWrite(19, LOW);
  }
  else if(event.temperature >= 24 && event.temperature < 25){
    digitalWrite(15, HIGH);
    digitalWrite(16, HIGH);
    digitalWrite(17, HIGH);
    analogWrite(17, 255);

    for(int i = 0; i <= 255; i++){
      analogWrite(19, i);
      delay(10);
    }
    for(int i = 255; i >= 0; i--){
      analogWrite(19, i);
      delay(10);
    }
  }
  else if(event.temperature >= 25){
    digitalWrite(15, HIGH);
    digitalWrite(16, HIGH);
    digitalWrite(17, HIGH);
    digitalWrite(19, HIGH);
    analogWrite(19, 255);

  }


}
