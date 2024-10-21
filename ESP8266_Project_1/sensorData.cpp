/*blah blah blah these are header notes it's Max Bernstein's code whatever

*/


#include <Arduino.h>
#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <stdlib.h>
#include "sensorData.h"
#include "dhtnew.h"
 


sensorData::sensorData(int pin, int node) {
    _pin = pin;
    _node = node;
    pinMode(_pin, INPUT_PULLUP);
}


bool sensorData::checkSwitch(sensorData sensor) {
  while(digitalRead(_pin) == HIGH) {
    delay(1000);
    Serial.print(" . ");
  }
  return true;
}


int sensorData::selectTimeZone() {
    Serial.println("Input the desired time zone (input 4 for PST): ");
    while (Serial.available() == 0) {
        delay(100);
    }
    int tZone = Serial.readStringUntil('\n').toInt();
    String output = "Time zone selected: " + String(tZone);
    Serial.println(output);
    return tZone;
}


void sensorData::defineTimeZone(int timezone) {
    _timezone = timezone;
    String tZone = String(_timezone);
    Serial.println("Sensor data assigned to: " + tZone);
}


String sensorData::readTime(HTTPClient& https, WiFiClientSecure& client) {
  String myTime;
  String timeURL;
  switch(_timezone) {
    case 1: timeURL = "America/New_York"; break;
    case 2: timeURL = "America/Chicago"; break;
    case 3: timeURL = "America/Denver"; break;
    case 4: timeURL = "America/Los_Angeles"; break;
    case 5: timeURL = "America/Anchorage"; break;
    case 6: timeURL = "Pacific/Honolulu"; break;
    case 7: timeURL = "America/Puerto_Rico"; break;
    default: timeURL = "America/Los_Angeles"; break;
  }
  String timeSite = "https://timeapi.io/api/Time/current/zone?timeZone=" + timeURL;
  Serial.println(timeSite);
  if (https.begin(client, timeSite)) {
    Serial.println("Connected to time site API");
    delay(2000);
    int httpCode = https.GET();
    if (httpCode > 0) {
      Serial.println("GET worked");
      String payload = https.getString();
      DynamicJsonDocument doc(2048);
      deserializeJson(doc, payload);
      const char* tempTime = doc["dateTime"];
      myTime = tempTime;
      myTime = myTime.substring(0, myTime.indexOf('.'));
      myTime.replace("T", "%20");
    }
    else {
      Serial.println("fuck: " + String(httpCode));
    }
    https.end();
    Serial.println("Time fetched: " + myTime);
  }
  else {
    Serial.println("\nFuck you and fuck this\n");
  }   
  return myTime;   
}


int sensorData::readSensorTemp(DHTNEW dht) {
    dht.read();
    String tempTemp = String(dht.getTemperature());
    Serial.println("Temp fetched: " + tempTemp);
    return dht.getTemperature();
}


int sensorData::readSensorHum(DHTNEW dht) {
    dht.read();
    String tempHum = String(dht.getHumidity());
    Serial.println("Humidity fetched: " + tempHum);
    return dht.getHumidity();
}


void sensorData::transmit(String myTime, int temp, int humidity, WiFiClientSecure& client, HTTPClient& https) {    
    String URL = "https://www.maxbernsteinprojects.com/mySQL_dBase.php";
    if (https.begin(client, URL)) {
        String node = "node_" + String(_node);
        String temperature = String(temp);
        temperature = temperature.substring(0, temperature.indexOf('.')); 
        String humidityS = String(humidity);
        humidityS = humidityS.substring(0, humidityS.indexOf('.'));
        String fullURL = (URL + "?node_name=" + node +"&temperature=" + temperature + "&humidity=" + humidityS + "&time_received=" + myTime);
        Serial.println(fullURL);
        https.end();
        https.begin(client, fullURL);
        int httpCode = https.POST(fullURL);
        if (httpCode > 0) {
            Serial.println("Successfully posted! Response code: " + String(httpCode));
        } else {
            Serial.print("Error on POST: ");
            Serial.println(https.errorToString(httpCode).c_str());
        }
    } 
    else {
        Serial.println("Unsuccessful posting");
    }  
    https.end(); 
}


bool sensorData::checkError(int temp, int humidity) {
    if (_node > 5 || _node < 1 || temp > 100 || temp < -10 || humidity > 100 || humidity < 0) {
       String node = String(_node);
       String temp = String(temp);
       String humidity = String(humidity);
       Serial.println("Data is out of range. Node = " + node + ", temp = " + temp + ", & humidity = " + humidity);
       return true;
    }
    else {
        
        return false;
    }
}


void sensorData::getWiFi(String ssid, String password) {
    Serial.println("Connecting to WiFi");
    WiFi.begin(ssid, password);

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


void getRandTempHum(int temp, int hum) {
    temp = random(-10, 100);
    hum = random(0, 100);
}
