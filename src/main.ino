#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ArduinoJson.h>
#include "config/hardware.h"


DHT dht(DHTPIN, DHTTYPE);


void setup() {
 // Schnittstelle einrichten
  Serial.begin(115200);
  Serial.println("DHT22 sensor!");

  esp_client.setServer(mqtt_server, 1883);
  esp_client.setCallback(callback);
  
  //Sensor einrichten
  dht.begin();
  
  
}

void loop() {
  //use the functions which are supplied by library.
  delay(1000);
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    //return;
  }
  // print the result to Terminal
  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.println(" *C ");
  
 
  WiFi.begin("17aqr54", "ottootto");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());  
 
  Serial.println("Start MQTT Verbindung");

  if (!esp_client.connected()) {
    reconnect(h,t);
    }

   // Daten nach Thinspeak senden
   SendSensorData(h,t);

  //Kleine Schleife zum empfangen von retain Messages 
  for ( uint8_t a = 0;a<10;a++){
    //MQTT bedienen
    esp_client.loop();
    delay(50);
    yield();
  }
  
  Serial.println("gehe schlafen");
  ESP.deepSleep(SLEEP_TIME,WAKE_RF_DEFAULT);
  delay(500);
  }