#ifndef TEST_DB
#define TEST_DB

#include "DHT.h"

//Daten für Thingspeak
const char* THINGSPEAK_HOST="api.thingspeak.com";    //Thingspeak API Host (NICHT ÄNDERN)
const int THINGSPEAK_PORT=80;                        //Der Port zum Zugriff auf Thingspeak (NICHT ÄNDERN)s
String THINGSPEAKAPIKEY="KU2N6AA4VK2QL15Z";   

//here we use pin IO14 of ESP32 to read data
#define DHTPIN 4
//our sensor is DHT22 type
#define DHTTYPE DHT22



//Schalfzeit, zwischen den Messungen
#define SLEEP_TIME 10 * 1000 * 1000


#endif