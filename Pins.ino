void setPinStatus()
{
  Serial.println(readString);
  int hasRelay = readString.indexOf("relay");
  if (hasRelay > 0)
  {
    int equalPos = readString.indexOf("=");
    int pinValue = readString.substring(hasRelay + 5, equalPos).toInt();
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
