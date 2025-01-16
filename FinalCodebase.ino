//TempandHumidity
#include "DHT.h"             // Library for DHT sensors
#define dhtPin 12            // data pin
#define dhtType DHT11        // DHT 11
DHT dht(dhtPin, dhtType);    // Initialise the DHT library
#include <SoftwareSerial.h>

SoftwareSerial ESP(2,3);

float humidityVal;           // humidity
float tempValC;              // temperature in degrees Celcius
float tempValF;              // temperature in degrees Fahrenheit
float heatIndexC;            // windchill in degrees Celcius
float heatIndexF;            // windchill in degrees Fahrenheit

const int dry = 1000; // value for dry sensor
const int wet = 730; // value for wet sensor

//LightIntensity Initialisations
int ldrPin = A1;              // LDR pin
int ldrVal = 0;               // Value of LDR
int ledPin = LED_BUILTIN;     // Build in LED pin

//SoilMoisture Initialisations
int sensorVal = analogRead(A0); 

void setup()
{ 
   
  Serial.begin(115200);
    ESP.begin(115200);

  dht.begin();               // start with reading the DHT sensor
  pinMode(LED_BUILTIN, OUTPUT);
}

String values;
void loop()
{
  

  // Sensor has a range of 239 to 595
  // We want to translate this to a scale or 0% to 100%
  // More info: https://www.arduino.cc/reference/en/language/functions/math/map/
  int percentageHumididy = map(sensorVal, wet, dry, 100, 0); 

  Serial.print(percentageHumididy);
  Serial.println("%");
  
  delay(100);

   ldrVal = analogRead(ldrPin);    // Read the analog value of the LDR
  Serial.println(ldrVal);         // Show the value in the serial monitor

  if (ldrVal < 200) {             // If the LDR value is lower than 200
    digitalWrite(ledPin, HIGH);   // Turn buildin LED on
  } else {
    digitalWrite(ledPin, LOW);    // Turn buildin LED off
  }

  delay(100);                     // Pause 100ms

   humidityVal = dht.readHumidity();        // get the humidity from the DHT sensor
  tempValC = dht.readTemperature();        // get the temperature in degrees Celcius from the DHT sensor
  tempValF = dht.readTemperature(true);    // get the temperature in degrees Fahrenheit from the DHT sensor

  // Check if all values are read correctly, if not try again and exit loop()
  if (isnan(humidityVal) || isnan(tempValC) || isnan(tempValF)) {
    Serial.println("Reading DHT sensor failed!");

    // end the loop() function
    return;
  }
  
  // Calculate the windchill in degrees Celcius
  heatIndexC = dht.computeHeatIndex(tempValC, humidityVal, false);

  // Calculate the windchill in degrees Fahrenheit
  heatIndexF = dht.computeHeatIndex(tempValF, humidityVal);

  // Print all values to the serial monitor
  // \t prints a tab character, \n a newline
  Serial.print(humidityVal);
  Serial.print("\t");
  Serial.print(tempValC);
  Serial.print("\n");
  
  delay(2000);

    values = String(tempValC)+','+String(humidityVal)+','+String(percentageHumididy)+','+String(ldrVal);

  delay(1000);
  Serial.flush();
  delay(1000);
  ESP.print(values);
  delay(2000);
}
