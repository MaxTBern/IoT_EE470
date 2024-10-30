#ifndef MYHEADER_H
#define MYHEADER_H

#include <Arduino.h>
#include <stdlib.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>


void getWifi(String ssid, String passwd);
String LEDstatus(WiFiClientSecure& client, HTTPClient& https);
void connect(WiFiClientSecure& client, HTTPClient& https);
void setLED(String state, int LED);
String RGBstatus(WiFiClientSecure& client, HTTPClient& https);
void setRGB(String state, int& red, int& green, int& blue, int& redPin, int& greenPin, int& bluePin);
void getRGBColor(WiFiClientSecure& client, HTTPClient& https, int& red, int& green, int& blue);

#endif
