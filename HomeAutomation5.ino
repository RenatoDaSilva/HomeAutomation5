#include <SPI.h>
#include <Ethernet.h>
#include <SD.h>
#include <ArduinoJson.h>

byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};
byte ip[] = {10, 0, 0, 25};

EthernetServer server(80);

String readString;
String names;

struct Config
{
  char *json;
  byte staticIP;
  long authKey;
};
Config config;

void setup()
{
  doSetup();
}

void loop()
{
  doLoop();
}
