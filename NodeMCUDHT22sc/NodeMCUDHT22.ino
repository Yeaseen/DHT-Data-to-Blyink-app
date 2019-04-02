/**
 * Example for reading temperature and humidity
 * using the DHT22 and ESP8266
 *
 * Copyright (c) 2016 Losant IoT. All rights reserved.
 * https://www.losant.com
 */
#define BLYNK_PRINT Serial


#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
 
#include <Wire.h>

#include <DHT.h>


char auth[] = "025fe969ce524fd38c21f8fc173fffaa";

char ssid[] = "PawnShopWIFI";
char pass[] = "samantha";

 
#define DHTPIN  14     // what digital pin the DHT22 is conected to
#define DHTTYPE DHT22   // there are multiple kinds of DHT sensors
BlynkTimer timer;
DHT dht(DHTPIN, DHTTYPE);
char temperature[] = "000.0 C";
char humidity[]    = "000.0 %";


void sendSensor()
{
  float h = dht.readHumidity();
  float t = dht.readTemperature(); // or dht.readTemperature(true) for Fahrenheit

  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  Serial.printf("Temperature = %5.1f°C\r\n", (float)t);
  Serial.printf("Humidity    = %5.1f %%\r\n\r\n", (float)h);
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  Blynk.virtualWrite(V6, h);
  Blynk.virtualWrite(V5, t);
}



void setup() {
  Serial.begin(115200);
  delay(1000);
 
  Wire.begin(4, 0);
  dht.begin();
  Blynk.begin(auth, ssid, pass);
  // Wait for serial to initialize.
  while(!Serial) { }

  Serial.println("Device Started");
  Serial.println("-------------------------------------");
  Serial.println("Running DHT!");
  Serial.println("-------------------------------------");

  timer.setInterval(1000L, sendSensor);
}


void loop() {

   // Read humidity
  //int RH = dht.readHumidity() * 10;
  //Read temperature in degree Celsius
  //int Temp = dht.readTemperature() * 10;
 
  // print data on serial monitor
  //Serial.printf("Temperature = %5.1f°C\r\n", (float)Temp/10);
  //Serial.printf("Humidity    = %5.1f %%\r\n\r\n", (float)RH/10);
  
  //delay(1000);

  Blynk.run();
  timer.run();


  
}
