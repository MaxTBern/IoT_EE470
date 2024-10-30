#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include "myheader.h"

const char* ssid = "TheShire";
const char* password = "Potaytoe";
WiFiClientSecure client;
HTTPClient https;
#define PUSH_BUTTON 10
#define LED 5
int red_pin = 14;
int green_pin = 12;
int blue_pin = 13;
int red;
int green;
int blue;


void setup() {
  Serial.begin(9600);
  client.setInsecure();
  pinMode(PUSH_BUTTON, INPUT_PULLUP);
  pinMode(LED, OUTPUT);
  pinMode(red_pin, OUTPUT);
  pinMode(green_pin, OUTPUT);
  pinMode(blue_pin, OUTPUT);
  getWifi(ssid, password);
}

void loop() {
  while(digitalRead(PUSH_BUTTON)==HIGH) {
    delay(250);
  }
  Serial.println("Changing LEDs...");
  setLED(LEDstatus(client, https), LED);
  getRGBColor(client, https, red, green, blue);
  setRGB(RGBstatus(client, https), red, green, blue, red_pin, green_pin, blue_pin);
  delay(1000);
}
