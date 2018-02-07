
#include <arduino.h>
#include "config/hardware.h"


void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
  
  payload[length] = '\0';
  String s = String((char*)payload);
  
  if(s.startsWith("update")){
      Serial.println("Update angefordert");
  }
}


void reconnect(float h,float t) {
    
  // Loop until we're reconnected
  while (!esp_client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (esp_client.connect("ESP8266Client")) {

      Serial.println("connected");
      // Once connected, publish an announcement...
      esp_client.publish("Status", "{\"Sensor\":\"DHT 22 meldet sich an\",\"Version\":\"0.9.123\"}");
      snprintf (msg, 50, "{\"Temperatur 2.0\":%.2f,\"Feuchte\":%.2f}", t,h);
      esp_client.publish("Sensor/DHT22/Kinderzimmer", msg);
      // ... and resubscribe
      esp_client.subscribe("inTopic");

    //Test des JSON
    JsonObject& root = jsonBuffer.createObject();
    root["app"]      = "Sensor_DHT_Deeplsleep";
    root["version"]  = "0.92";
    root["host"]     = String(HOSTNAME);
    root["ip"]       = WiFi.localIP().toString();
    root["mac"]      = WiFi.macAddress();
    root["rssi"]     = String(WiFi.RSSI());
    root["uptime"]   = 1351824120;
    //root["Spannung"]  = String(ESP.getVcc()).c_str();
    root["Temperatur"]   = String(t);
    root["Luftfeuchte"]  = String(h);

    //und veröffentlichen über MQQT
    root.printTo(msg,sizeof(msg));
    esp_client.publish("Sensor/Kinderzimmer/data", msg);


    } else {
      Serial.print("failed, rc=");
      Serial.print(esp_client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}