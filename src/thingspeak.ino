#include <arduino.h>
#include <ESP8266WiFi.h>
#include "config/hardware.h"


void SendSensorData(float h,float t) {
  
  
  Serial.print(F("Verbinde mit "));
  Serial.println(THINGSPEAK_HOST);

  WiFiClient client;

  delay(200);

  if (!client.connect(THINGSPEAK_HOST, THINGSPEAK_PORT)) {
    Serial.println(F(""));
    Serial.println(F("Verbindung mit Thingspeak-Server fehlgeschlagen!"));
  } else {
    Serial.println(F("Verbindung mit Thingspeak-Server erfolgreich hergestellt"));
    Serial.println(F("Sende Daten an Thingspeak Channel..."));

    String POSTString ="api_key=";
    POSTString += THINGSPEAKAPIKEY.c_str();
    POSTString += "&field1=";
    POSTString += t;
    POSTString += "&field2=";
    POSTString += h;
    
    client.print(F("POST /update HTTP/1.1\n")); 
    client.print(F("HOST: "));
    client.print(THINGSPEAK_HOST);
    client.print(F("\n"));
    client.print(F("X-THINGSPEAKAPIKEY:"));
    client.print(THINGSPEAKAPIKEY.c_str());
    client.print(F("\n"));
    client.print(F("Connection: close\n")); 
    client.print(F("Content-Type: application/x-www-form-urlencoded\n")); 
    client.print(F("Content-Length: "));
    client.print(POSTString.length()); 
    client.print(F("\n\n"));
    client.print(POSTString);

    delay(1000);
        
    client.stop();
    
    Serial.println(F("Verbindung zum Server beendet"));
    Serial.println(F("Daten an Thingspeak Channel gesendet"));
  }  

 
}