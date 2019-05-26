#include <SPI.h>
#include <Ethernet.h>
#include <SD.h>

byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};
byte ip[] = {10, 0, 0, 25};

EthernetServer server(80);
File webFile;

String readString;

void setup()
{

  Serial.begin(9600);

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

  Serial.println("Carregando HTML");
  webFile = SD.open("index.html");
  if (webFile)
  {
    while (webFile.available())
    {
      Serial.println("Lendo HTML");
      cl.write(webFile.read());
    }
    webFile.close();
  }

  // cl.println("<HTML>");
  // cl.println("<BODY>");
  // cl.println("<H1>HomeAutomation 5</H1>");
  // cl.println("<hr />");
  // cl.println("<br />");

  // cl.println("<button onclick=\"window.location.href = '/?relay2=2';\">Relay 2</button><br />");
  // cl.println("<button onclick=\"window.location.href = '/?relay3=2';\">Relay 3</button><br />");
  // cl.println("<button onclick=\"window.location.href = '/?relay4=2';\">Relay 4</button><br />");
  // cl.println("<button onclick=\"window.location.href = '/?relay5=2';\">Relay 5</button><br />");
  // cl.println("<button onclick=\"window.location.href = '/?relay6=2';\">Relay 6</button><br />");
  // cl.println("<button onclick=\"window.location.href = '/?relay7=2';\">Relay 7</button><br />");
  // cl.println("<button onclick=\"window.location.href = '/?relay8=2';\">Relay 8</button><br />");
  // cl.println("<button onclick=\"window.location.href = '/?relay9=2';\">Relay 9</button><br />");

  // cl.println("</BODY>");
  // cl.println("</HTML>");
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
  pinMode(4, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(2, OUTPUT);
}
