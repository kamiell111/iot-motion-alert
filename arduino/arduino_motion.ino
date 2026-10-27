
#include <SoftwareSerial.h>

// Arduino RX = D10, TX = D11
SoftwareSerial espSerial(10, 11);

const int trigPin = 3;
const int echoPin = 4;
const int ledPin = 13;
const int buzzerPin = 8;

const float batasDeteksi = 50.0; // centimeter
const float batasReset = 60.0;   // hysteresis
bool objekTerdeteksi = false;

unsigned long ukurJarak() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(3);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  return pulseIn(echoPin, HIGH, 30000UL);
}

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);

  Serial.begin(9600);
  espSerial.begin(9600);

  Serial.println("IoT Motion Detection Ready");
}

void loop() {
  unsigned long durasi = ukurJarak();

  if (durasi == 0) {
    delay(100);
    return;
  }

  float jarak = durasi * 0.0343 / 2.0;

  Serial.print("Jarak: ");
  Serial.print(jarak);
  Serial.println(" cm");

  if (!objekTerdeteksi && jarak <= batasDeteksi) {
    objekTerdeteksi = true;

    digitalWrite(ledPin, HIGH);
    tone(buzzerPin, 2000, 500);

    // Kirim perintah ke ESP8266
    espSerial.println("DETECTED");
    Serial.println("Objek terdeteksi!");
  }

  if (objekTerdeteksi && jarak >= batasReset) {
    objekTerdeteksi = false;

    digitalWrite(ledPin, LOW);
    noTone(buzzerPin);

    Serial.println("Area kembali kosong.");
  }

  delay(100);
}
