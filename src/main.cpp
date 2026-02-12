#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>
#include <LittleFS.h>
#include <TFT_eSPI.h>

const char* ssid     = "otto hotspot";
const char* password = "";
int alarmH = -1;
int alarmM = -1;

WebServer server(80);
TFT_eSPI tft = TFT_eSPI();

void displaySetup(){
  Serial.begin(115200);
  tft.init();
  tft.setRotation(0);
  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  tft.setTextSize(2);
  tft.setCursor(10, 10);
  tft.print("Hallo GC9A01!");
}

// Erwartet z.B. POST /api/set mit Form-Feld "alarm" (z.B. "07:30")
void handleApiSetForm() {
  // wird bereits nur für HTTP_POST registriert, der Check ist optional
  if (!server.hasArg("hh") || !server.hasArg("mm")) {
    server.send(400, "text/plain", "Missing hh or mm");
    return;
  }

  // toInt() gibt 0 zurück, wenn es kein Integer ist -> deswegen zusätzlich validieren
  String hhS = server.arg("hh");
  String mmS = server.arg("mm");

  // genau 2 Stellen
  if (hhS.length() != 2 || mmS.length() != 2) {
    server.send(400, "text/plain", "Need 2 digits");
    return;
  }

  // nur Ziffern
  for (size_t i = 0; i < hhS.length(); i++) {
    if (!isDigit(hhS[i])) { server.send(400, "text/plain", "hh not numeric"); return; }
  }
  for (size_t i = 0; i < mmS.length(); i++) {
    if (!isDigit(mmS[i])) { server.send(400, "text/plain", "mm not numeric"); return; }
  }

  int hh = hhS.toInt();
  int mm = mmS.toInt();

  // Bereich prüfen
  if (hh < 0 || hh > 23 || mm < 0 || mm > 59) {
    server.send(400, "text/plain", "Invalid time");
    return;
  }

  alarmH = hh;
  alarmM = mm;

  Serial.printf("Alarm gesetzt: %02d:%02d\n", alarmH, alarmM);

  server.send(200, "text/plain", "OK");
}

void handleStatus() {
  String json = "{";
  json += "\"ip\":\"" + WiFi.localIP().toString() + "\",";
  json += "\"rssi\":" + String(WiFi.RSSI()) + ",";
  json += "\"alarmH\":" + String(alarmH) + ",";
  json += "\"alarmM\":" + String(alarmM);
  json += "}";
  server.send(200, "application/json", json);
}

void setup() {
  Serial.begin(115200);
  delay(200);

  // 1) WLAN verbinden (STA)
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(250);
  }
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());

  // 2) LittleFS mounten (true = optional format, falls Mount fehlschlägt)
  if (!LittleFS.begin(true)) {
    Serial.println("LittleFS mount fehlgeschlagen");
    while (true) delay(1000);
  }

  // 3) Statische Dateien ausliefern
  // Erwartet Dateien in LittleFS: /index.html, /app.js, /style.css
  server.serveStatic("/", LittleFS, "/index.html");
  server.serveStatic("/app.js", LittleFS, "/app.js");
  server.serveStatic("/style.css", LittleFS, "/style.css");
  server.on("/api/set", HTTP_POST, handleApiSetForm);
  server.on("/status", HTTP_GET, handleStatus);

  // Optional: 404 für alles andere
  server.onNotFound([]() {
    server.send(404, "text/plain", "Not found");
  });

  server.begin();
  Serial.println("HTTP Static Server gestartet");
}

void loop() {
  server.handleClient(); // wichtig, sonst antwortet der Server nicht
}

void sendData(){
  //Zeit an Display senden
}