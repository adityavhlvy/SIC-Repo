#include <WiFi.h>
#include <HTTPClient.h>

#define AIR_QUALITY_PIN 34  // GPIO yang digunakan untuk data sensor udara

const char* ssid = "your_SSID";          // Ganti dengan nama SSID WiFi Anda
const char* password = "your_PASSWORD";  // Ganti dengan password WiFi Anda
const char* serverName = "http://your_server_ip:your_server_port/your_endpoint";  // Ganti dengan URL server Anda

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  Serial.println("Connecting to WiFi...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting...");
  }

  Serial.println("Connected to WiFi");
}

void loop() {
  int airQualityValue = analogRead(AIR_QUALITY_PIN);
  float voltage = airQualityValue * (3.3 / 4095.0);  // Konversi ke voltase (untuk sensor analog)

  Serial.print("Air Quality (Voltage): ");
  Serial.println(voltage);

  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;

    http.begin(serverName);
    http.addHeader("Content-Type", "application/json");

    String httpRequestData = "{\"air_quality\":" + String(voltage) + "}";
    int httpResponseCode = http.POST(httpRequestData);

    if (httpResponseCode > 0) {
      String response = http.getString();
      Serial.println(httpResponseCode);
      Serial.println(response);
    } else {
      Serial.print("Error on sending POST: ");
      Serial.println(httpResponseCode);
    }

    http.end();
  } else {
    Serial.println("WiFi Disconnected");
  }

  delay(10000);  // Mengirim data setiap 10 detik
}
