void doSetup()
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
