#ifndef WIFI_HPP
#define WIFI_HPP

#include <Arduino.h>
#include <WiFi.h>
#include <ArduinoJson.h>

enum CON_STATUS {
	DISCONNECTED,
	CONNECTED,
	WAITING_SSID,
	WAITING_PSWD,
	WAITING_NAME,
};

class WCON { // wifi connection
private:
    uint16_t connection_timeout = 10000; // 10 seconds
    CON_STATUS m_status;
    CON_STATUS prev_status; // only connected or disconnected;
    String m_ssid;
    String m_pswd;
    String m_name;

public:
    // setters
    void ssid(String id);
    void pswd(String p);
    void name(String n);
    void status(CON_STATUS s);

    // getters
    String ssid() { return m_ssid; }
    String pswd() { return m_pswd; }
    String name() { return m_name; }
    CON_STATUS status() { return m_status; }

    void init();
    int connect();
    void disconnect();
    void scan(bool hidden);
};

#endif