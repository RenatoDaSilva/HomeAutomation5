bool validateAuthKey()
{
    String textToFind = "&auth_key=";

    int posAuthKey = readString.indexOf(textToFind);
 
    if (posAuthKey == 0)
    {
        Serial.println("Não foi informada chave de autorização");
        return false;
    }

    posAuthKey += textToFind.length();

    int authKeyFromRequest = readString.substring(posAuthKey, posAuthKey + 6).toInt();
    Serial.println(authKeyFromRequest);
    if (authKeyFromRequest != config.authKey)
    {
        Serial.println("Chave de autorização não confere");
        return false;
    }
    return true;
}
