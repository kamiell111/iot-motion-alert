
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <ESP8266HTTPClient.h>
#include <SoftwareSerial.h>

// RX = D5, TX = D6
SoftwareSerial arduinoSerial(D5, D6);

// Isi sendiri sebelum digunakan.
// Jangan unggah token asli ke repository publik.
const char* WIFI_SSID = "NAMA_WIFI";
const char* WIFI_PASSWORD = "PASSWORD_WIFI";
const char* BOT_TOKEN = "ISI_TOKEN_BOT";
const char* CHAT_ID = "ISI_CHAT_ID";

WiFiClientSecure secureClient;

bool sendTelegram(String message) {
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("WiFi terputus.");
    return false;
  }

  HTTPClient https;
  secureClient.setInsecure(); // Demo; produksi sebaiknya verifikasi sertifikat.

  String url =
    "https://api.telegram.org/bot" +
    String(BOT_TOKEN) + "/sendMessage";

  if (!https.begin(secureClient, url)) {
    Serial.println("Gagal memulai HTTPS.");
    return false;
  }

  https.addHeader("Content-Type", "application/json");

  message.replace("\\", "\\\\");
  message.replace("\"", "\\\"");
  message.replace("\n", "\\n");

  String body = "{\"chat_id\":\"" + String(CHAT_ID) +
                "\",\"text\":\"" + message + "\"}";

  int status = https.POST(body);
  String response = https.getString();

  Serial.printf("HTTP status: %d\n", status);

  https.end();
  return status >= 200 && status < 300;
}

void setup() {
  Serial.begin(115200);
  arduinoSerial.begin(9600);

  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  Serial.print("Menghubungkan WiFi");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWiFi terhubung!");
  Serial.println(WiFi.localIP());

  sendTelegram("Sistem IoT aktif. Pemantauan dimulai.");
}

void loop() {
  if (arduinoSerial.available()) {
    String command = arduinoSerial.readStringUntil('\n');
    command.trim();

    if (command == "DETECTED") {
      Serial.println("Peringatan: objek terdeteksi!");

      sendTelegram(
        "PERINGATAN IoT\n"
        "Objek terdeteksi oleh sensor HC-SR04.\n"
        "Silakan periksa area yang dipantau."
      );
    }
  }
}
