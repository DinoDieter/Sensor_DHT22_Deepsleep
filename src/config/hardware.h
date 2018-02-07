#ifndef TEST_DB
#define TEST_DB

#include "DHT.h"
#include <PubSubClient.h>
//#include <ArduinoOTA.h>
#include <ArduinoJson.h>

//Daten für Thingspeak
const char* THINGSPEAK_HOST="api.thingspeak.com";    //Thingspeak API Host (NICHT ÄNDERN)
const int THINGSPEAK_PORT=80;                        //Der Port zum Zugriff auf Thingspeak (NICHT ÄNDERN)s
String THINGSPEAKAPIKEY="KU2N6AA4VK2QL15Z";   

//here we use pin IO14 of ESP32 to read data
#define DHTPIN 4
//our sensor is DHT22 type
#define DHTTYPE DHT22

// MQTT Server
WiFiClient client;
 //MQTT vorbereiten
 PubSubClient esp_client(client);


const char* mqtt_server = "192.168.4.38";
#define HOSTNAME "ESP32_Board_WROOM32"
char msg[MQTT_MAX_PACKET_SIZE];

// JSON Variablen
StaticJsonBuffer<MQTT_MAX_PACKET_SIZE> jsonBuffer;

// Deepsleep
#define uS_TO_S_FACTOR 1000000  /* Conversion factor for micro seconds to seconds */
#define TIME_TO_SLEEP  30        /* Time ESP32 will go to sleep (in seconds) */

//Schalfzeit, zwischen den Messungen  sekunden * ms * us
#define SLEEP_TIME 300 * 1000 * 1000


#endif