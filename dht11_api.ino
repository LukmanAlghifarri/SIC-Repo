#include <WiFi.h>
#include <HTTPClient.h>
#include "DHT.h"

#define DHT11PIN 13
DHT dht(DHT11PIN, DHT11);

const char* ssid = "ESP32 Kelompok 3";
const char* password = "algibzhat123456";
const char* serverName = "http://127.0.0.1:5000/sensor/data";  // Ganti <IP_ADDRESS> dengan IP address server Flask

void setup() {
  Serial.begin(115200);
  dht.begin();
  
  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Connected to WiFi");
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    float temperature = dht.readTemperature();
    float humidity = dht.readHumidity();
    
    if (isnan(temperature) || isnan(humidity)) {
      Serial.println("Failed to read from DHT sensor!");
      return;
    }

    HTTPClient http;
    http.begin(serverName);

    // Specify content-type header
    http.addHeader("Content-Type", "application/json");

    // Prepare JSON payload
    String httpRequestData = "{\"temperature\":\"" + String(temperature) + "\", \"kelembapan\":\"" + String(humidity) + "\"}";
    
    // Send HTTP POST request
    int httpResponseCode = http.POST(httpRequestData);

    // Check the response code
    if (httpResponseCode > 0) {
      String response = http.getString();
      Serial.println(httpResponseCode);
      Serial.println(response);
    } else {
      Serial.print("Error on sending POST: ");
      Serial.println(httpResponseCode);
    }

    // Free resources
    http.end();
  } else {
    Serial.println("WiFi Disconnected");
  }
  // Delay before next request
  delay(10000);
}
