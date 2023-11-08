#include <Arduino.h>

#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ArduinoJson.h>
#include <ESP8266HTTPClient.h>

ESP8266WiFiMulti WiFiMulti;

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFiMulti.addAP("PC-LHQ", "123456789liu");
}

void loop() {
  int i=0;
  if ((WiFiMulti.run() == WL_CONNECTED)) {

    WiFiClient client;
    HTTPClient http;

    http.begin(client, "http://getweather.market.alicloudapi.com/lundear/weather1d?areaCode=420100");
    http.addHeader("Authorization", "APPCODE xxxxxxxxxx");
    int httpCode = http.GET();
    if (httpCode > 0) {
      if (httpCode == HTTP_CODE_OK) {
        String payload;
        payload = http.getString();
        Serial.println();
        Serial.print(payload);
        for(int i=0;i<24;i++)
        delay(600000);
      } else {
        Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
      }
      http.end();
    }
  }
}
