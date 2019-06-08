void getConfig()
{
    const size_t capacity = JSON_OBJECT_SIZE(2) + 30;
    DynamicJsonDocument doc(capacity);

    deserializeJson(doc, config.json);

    config.staticIP = doc["ip"];
    config.authKey = doc["auth_key"];
}

//  StaticJsonDocument<512> doc;

//  DeserializationError error = deserializeJson(doc, file);
//  if (error)
//    Serial.println(F("Falha ao ler o arquivo de configuração"));

//  authKey = doc["auth_key"];
//  local_ip = doc["ip"];

// byte splitStaticIPtoArrayIP(char* charIP) 
// {
//     const size_t capacity = JSON_OBJECT_SIZE(2) + 30;
//     DynamicJsonDocument doc(capacity);

//     deserializeJson(doc, config.staticIP);

//     config.staticIP = doc["ip"];
//     config.authKey = doc["auth_key"];
// }
