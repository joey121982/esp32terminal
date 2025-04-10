#include "wifi.hpp"

// setters
void WCON::ssid(String id) {
    m_ssid = id;
    m_status = prev_status;
}
void WCON::pswd(String p) {
    m_pswd = p;
    m_status = prev_status;
}
void WCON::name(String n) {
    m_name = n;
    m_status = prev_status;
}
void WCON::status(CON_STATUS s) {
    m_status = s;
}

void WCON::init() {
    WiFi.mode(WIFI_STA);
    WiFi.disconnect();
    m_status = DISCONNECTED;
    prev_status = DISCONNECTED;
    delay(100);
}

int WCON::connect() {
    if (!m_ssid.length()) {
        Serial.println("No SSID provided.");
    }
    if (!m_pswd.length()) {
        Serial.println("No PSWD provided.");
    }

    int result = 1;
    WiFi.setHostname(m_name.c_str());
    WiFi.begin(m_ssid.c_str(), m_pswd.c_str());
    auto timer = millis();
    while(WiFi.status() != WL_CONNECTED) {
        Serial.print('.');
        delay(500);
        if(millis() - timer > connection_timeout) {
            result = 0; // failed to connect
            break;
        }
    }
    if(result == 0) {
        Serial.println("Failed to connect to \"" + m_ssid + "\".\n");
    } else {
        m_status = CONNECTED;
        prev_status = CONNECTED;
        Serial.print("Connected to \"" + m_ssid + "\", with ip: ");
        Serial.println(WiFi.localIP());
    }
    return result;
}

void WCON::disconnect() {
    if (prev_status == DISCONNECTED) {
        Serial.println("Not connected to any network.");
        return;
    }
    WiFi.disconnect();
    m_status = DISCONNECTED;
    prev_status = DISCONNECTED;
    Serial.println("Disconnected from " + m_ssid + ".");
}

void WCON::scan(bool hidden) {
    Serial.println("Scanning for networks...");
    auto timer = millis();
    int count = WiFi.scanNetworks(false, hidden);
    if (count > 0) {
        for(int index = 0; index < count; index++) {
            bool open = WiFi.encryptionType(index) == WIFI_AUTH_OPEN;
            String SSID = WiFi.SSID(index);
            if(!SSID.length()) {
                SSID = "HIDDEN NETWORK";
            }
            
            Serial.print(index + 1);
            Serial.print(". ");
            Serial.print(SSID);
            Serial.print(" (");
            Serial.print(WiFi.RSSI(index));
            Serial.print("dB)");
            Serial.print(" - ");
            Serial.println((open) ? "Open" : "Protected");}
    }
    auto time = millis() - timer;
    Serial.print("Scan complete. (Took ");
    Serial.print(time / 1000);
    Serial.print(".");
    time %= 1000;
    if(time < 100) Serial.print('0');
    Serial.print(time);
    Serial.println(" seconds.)");
}
