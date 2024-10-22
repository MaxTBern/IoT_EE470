/*I'M NOT WRITING A HEADER YOU CAN'T MAKE ME


*/

#include <Arduino.h>
#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <stdlib.h>
#include "dhtnew.h"
#include "sensorData.h"

const char* ssid = "";
const char* password = "";

DHTNEW dht(10);
WiFiClientSecure client;
HTTPClient https;
sensorData sensor(16, 1);
String myTime;
int temperature;
int humidity;
String test;
int timezone;


void setup() {
  Serial.begin(9600);
  client.setInsecure();
  timezone = sensor.selectTimeZone();
  sensor.defineTimeZone(timezone);
  sensor.getWiFi(ssid, password);
  dht.setHumOffset(-800);
  dht.setTempOffset(-595);
}



void loop() {
  sensor.checkSwitch(sensor);

  myTime = sensor.readTime(https, client);  

  temperature = sensor.readSensorTemp(dht);
  
  humidity = sensor.readSensorHum(dht);

  if (!(sensor.checkError(temperature, humidity))) {
    Serial.println("Values are a go!");
    while (Serial.available()) {
        Serial.read();
    }while (Serial.available() == 0) {
        delay(100);
    }
    sensor.transmit(myTime, temperature, humidity, client, https);
  }
}


