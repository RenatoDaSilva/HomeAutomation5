#include <SD.h>

void initializeSDCard()
{
    Serial.println("Incializando SD card...");
    if (!SD.begin(4))
    {
        Serial.println("ERRO - falha ao inicializar SD card!");
        return;
    }

    Serial.println("SUCCESSO - SD card inicializado.");
}

void getNames()
{
    char c;
    File file = SD.open("names.txt");
    if (file)
    {
        while (file.available())
        {
            c = file.read();
            names += c;
        }
        file.close();
    }
}

void loadConfiguration()
{
    char c;
    File file = SD.open("config.txt");
    if (file)
    {
        while (file.available())
        {
            c = file.read();
            config.json += c;
        }
        file.close();
    }
}
