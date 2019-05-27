#include <SPI.h>
#include <Ethernet.h>
#include <SD.h>

byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};
byte ip[] = {10, 0, 0, 25};

EthernetServer server(80);
File webFile;

String readString;
String names;

void setup()
{

  Serial.begin(9600);

  initializeSDCard();

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

void setPinStatus()
{
  int temRelay = readString.indexOf("?relay");
  if (temRelay > 0)
  {
    int equalPos = readString.indexOf("=");
    int pinValue = readString.substring(temRelay + 6, equalPos).toInt();
    int pinStatus = readString.substring(equalPos + 1, equalPos + 2).toInt();

    if (pinValue == 4)
    {
      Serial.println("Não é possível usar o pino 4");
      Serial.println("ele é usado pelo cartão SD");
      return;
    }

    if (pinStatus == 2)
    {
      if (digitalRead(pinValue) == 1)
      {
        pinStatus = 0;
      }
      else
      {
        pinStatus = 1;
      }
    }

    digitalWrite(pinValue, pinStatus);

    Serial.print("Relay ");
    Serial.print(pinValue);
    Serial.print(" alternou para o estado ");
    Serial.println(pinStatus);
  }
}

void getHTML(EthernetClient cl)
{
  cl.println("HTTP/1.1 200 OK");
  cl.println("Content-Type: text/html");
  cl.println();

  cl.println("<HTML>");
  cl.println("<BODY>");

  cl.println(names);

  cl.println("</BODY>");
  cl.println("</HTML>");
}

void readLastStates()
{
}

void writeState()
{
}

void setPins()
{
  pinMode(9, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(2, OUTPUT);
}

void initializeSDCard()
{
  Serial.println("Incializando SD card...");
  if (!SD.begin(4))
  {
    Serial.println("ERRO - falha ao inicializar SD card!");
    return;
  }
  Serial.println("SUCCESS - SD card inicializado.");
}

void getNames()
{
  char c;
  webFile = SD.open("names.txt");
  if (webFile)
  {
    while (webFile.available())
    {
      c = webFile.read();
      names += c;
    }
    webFile.close();
  }
  return names;
}
