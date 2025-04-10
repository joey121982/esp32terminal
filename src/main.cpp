#include <Arduino.h>
#include <WiFi.h>
#include <ArduinoJson.h>

#include "wifi.hpp"

WCON wifi;

void setup() {
	Serial.begin(115200);
	wifi.init();
}

void loop() {
	if(Serial.available()) {
		String input = String();
		
		// while(Serial.available()) {
		// 	char byte = Serial.read();
		// 	if(byte == '\r' || byte == '\n' && input.length() == 0) continue;
		// 	if(byte == '\r' || byte == '\n') break;
		// 	input += byte;
		// }

		input = Serial.readStringUntil('\n');
		input.remove(input.length() - 1);

		if(wifi.status() == WAITING_SSID) {
			
			wifi.ssid(input);
			Serial.println("Successfully received SSID.");
			
		} else if(wifi.status() == WAITING_PSWD) {
			
			wifi.pswd(input);
			Serial.println("Successfully received PSWD.");
			
		} else if(wifi.status() == WAITING_NAME) {
			
			wifi.name(input);
			Serial.println("Successfully received NAME.");
			
		} else if(input == "ssid") {

			wifi.status(WAITING_SSID);

		} else if (input == "pswd") {
			
			wifi.status(WAITING_PSWD);
			
		} else if (input == "name") {
			
			wifi.status(WAITING_NAME);
			
		} else if (input == "connect") {
			
			int status = wifi.connect();
			
		} else if (input == "disconnect") {
			
			wifi.disconnect();
			
		} else if (input == "scan") {
			
			wifi.scan(false);
			
		} else if (input == "scan hidden") {
			
			wifi.scan(true);
			
		}
	}
	delay(10);
}