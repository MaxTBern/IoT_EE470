#include <Arduino.h>
#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <stdlib.h>
#include "myheader.h"

void getWifi(String ssid, String passwd) {
    Serial.println("Connecting to WiFi");
    WiFi.begin(ssid, passwd);

    while (WiFi.status() != WL_CONNECTED) {
        delay(100);
        Serial.print(".");
    }
    //Print connection details
    Serial.print("\nConnected to: ");
    Serial.println(WiFi.SSID());
    Serial.print("IP Address:\t");
    Serial.println(WiFi.localIP());
    Serial.print("Channel:\t");
    Serial.println(WiFi.channel());
    Serial.print("RSSI:\t");
    Serial.println(WiFi.RSSI());
    Serial.print("DNS IP:\t");
    Serial.println(WiFi.dnsIP(1));
    Serial.print("Gateway IP:\t");
    Serial.println(WiFi.gatewayIP());
    Serial.print("MAC Address:\t");
    Serial.println(WiFi.macAddress());
    Serial.println("--------------");
}


void connect(WiFiClientSecure& client, HTTPClient& https) {
    String URL = "https://maxbernsteinprojects.com/API_Assignment/ledstatus.txt";
    if (https.begin(client, URL)) {
        int httpCode = https.GET();
        if (httpCode > 0) {
            Serial.println("Successfully connected! Response code: " + String(httpCode));
            if (httpCode == HTTP_CODE_OK) {
                String payload = https.getString();
                Serial.println("Response payload:");
                Serial.println(payload);
            }        
        } else {
            Serial.print("Error on GET: ");
            Serial.println(https.errorToString(httpCode).c_str());
        }
        https.end();
    } 
    else {
        Serial.println("Unsuccessful connection");
    }  
}


String LEDstatus(WiFiClientSecure& client, HTTPClient& https) {
    String orders;
    if (https.begin(client, "https://maxbernsteinprojects.com/API_Assignment/ledstatus.txt")) {
        int httpCode = https.GET();
        if (httpCode > 0) {
            orders = https.getString();
        }
        else {
            Serial.println("GET failed");
        } 
    } 
    Serial.println("LEDstatus = " + orders);
    delay(25);
    https.end();
    return orders; 
}


String RGBstatus(WiFiClientSecure& client, HTTPClient& https) {
    String rgbStatus;
    if (https.begin(client, "https://maxbernsteinprojects.com/API_Assignment/rgbstatus.txt")) {
        int httpCode = https.GET();
        if (httpCode > 0) {
            Serial.println("RGBstatus GET Worked");
            String payload = https.getString();
            DynamicJsonDocument doc(2048);
            deserializeJson(doc, payload);
            rgbStatus = doc["STATUS"].as<String>();
            Serial.println("rgbStatus in loop = " + rgbStatus); 
        }
    }
    else {
        Serial.println("GET FAILED FOR RGBSTATUS");
    }
    Serial.println("RGBstatus = " + rgbStatus);
    delay(100);
    https.end();
    return rgbStatus;
}


void setLED(String state, int LED) {
    if (state == "on") {
        digitalWrite(LED, HIGH);
    } else {
        digitalWrite(LED, LOW);
    }
    delay (100);
}


void setRGB(String state, int& red, int& green, int& blue, int& redPin, int& greenPin, int& bluePin) {
    if (state == "on") {
        analogWrite(redPin, red);
        analogWrite(greenPin, green);
        analogWrite(bluePin, blue);
        Serial.println("Should be on!");
    } else {
        analogWrite(redPin, LOW);
        analogWrite(greenPin, LOW);
        analogWrite(bluePin, LOW);
        Serial.println("Should be off!");
    }
    delay (100);
}


void getRGBColor(WiFiClientSecure& client, HTTPClient& https, int& red, int& green, int& blue) {
    if (https.begin(client, "https://maxbernsteinprojects.com/API_Assignment/rgbstatus.txt")) {
        int httpCode = https.GET();
            if (httpCode > 0) {
                Serial.println("getRGBColor GET Worked");
                String payload = https.getString();
                DynamicJsonDocument doc(1024);
                deserializeJson(doc, payload);
                String redStr = doc["RED"].as<String>();
                red = doc["RED"].as<int>();
                Serial.println("Red value is: " + redStr);
                String greenStr = doc["GREEN"].as<String>();
                green = doc["GREEN"].as<int>();
                Serial.println("Green value is: " + greenStr);
                String blueStr = doc["BLUE"].as<String>();
                Serial.println("Blue value is: " + blueStr);
                blue = doc["BLUE"].as<int>();
            }
        https.end();
    }
    else {
        Serial.println("CONNECT FAILED IN GETRGBCOLOR");
    }
}
