#ifndef SENSOR_DATA_H
#define SENSOR_DATA_H


#include "dhtnew.h"

class sensorData {
    public:
        bool checkSwitch(sensorData sensor);
        String readTime(HTTPClient& https, WiFiClientSecure& client);
        int readSensorTemp(DHTNEW dht); 
        int readSensorHum(DHTNEW dht);
        void transmit(String myTime, int temp, int humidity, WiFiClientSecure& client, HTTPClient& https);
        bool checkError(int timezone, int temp);
        void getWiFi(String ssid, String password);
        int selectTimeZone();
        void defineTimeZone(int timezone);
        sensorData(int pin, int node);
    private:
        int _timezone;
        int _node;
        int _pin;
};


#endif
