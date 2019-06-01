#include <SPI.h>
#include <Ethernet.h>

byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};
byte ip[] = {10, 0, 0, 25};

EthernetServer server(80);

String readString;
String names;

struct Config
{
  char* json;
  byte staticIP;
  long authKey;
};
Config config;

void setup()
{

  Serial.begin(9600);

  initializeSDCard();

  loadConfiguration();

  getNames();

  setPins();

  readLastStates();

  Ethernet.begin(mac, ip);
  server.begin();
  Serial.print("Servidor local em http:\\\\");
  Serial.println(Ethernet.localIP());
}

void loop()
{
  EthernetClient client = server.available();
  if (client)
  {
    while (client.connected())
    {
      if (client.available())
      {
        char c = client.read();

        if (readString.length() < 100)
        {
          readString += c;
        }

        if (c == '\n')
        {
          getHTML(client);

          delay(1);
          client.stop();

          setPinStatus();

          writeState();

          readString = "";
        }
      }
    }
  }
}
