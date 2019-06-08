void doLoop()
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
