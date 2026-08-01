#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "Wokwi-GUEST";
const char* password = "";

unsigned long lastTime = 0;
unsigned long interval = 2000;

String serverURL = "http://YOUR_PC_IP/Robot-Control-Panel-main/get_state.php";
void setup() {
  Serial.begin(115200);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi...");
  }

  Serial.println("WiFi Connected!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
}

void loop() {

  if (millis() - lastTime > interval) {

    if (WiFi.status() == WL_CONNECTED) {

      HTTPClient http;

      http.begin(serverURL);

      int httpResponseCode = http.GET();

      Serial.print("HTTP Response Code: ");
      Serial.println(httpResponseCode);

      if (httpResponseCode > 0) {

        String payload = http.getString();

        Serial.println("Database Response:");
        Serial.println(payload);

      } else {

        Serial.println("Error getting data");

      }

      http.end();

    } else {
      Serial.println("WiFi Disconnected");
    }

    lastTime = millis();
  }
}
