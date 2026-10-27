
# IoT Motion Alert

Sistem pemantauan area berbasis Arduino Uno,
sensor ultrasonik HC-SR04, dan ESP8266.

## Fitur
- Mendeteksi objek berdasarkan jarak.
- Menyalakan LED sebagai indikator.
- Membunyikan buzzer sebagai peringatan.
- Mengirim notifikasi ke Telegram melalui Wi-Fi.

## Komponen
- Arduino Uno
- Sensor HC-SR04
- NodeMCU ESP8266
- LED dan buzzer
- Breadboard dan kabel jumper
- Kabel USB dan sumber daya yang sesuai

## Alur sistem

HC-SR04
    -> Arduino Uno
    -> ESP8266
    -> Wi-Fi
    -> Telegram

## Instalasi
1. Buka kode Arduino di Arduino IDE.
2. Unggah arduino_motion.ino ke Arduino Uno.
3. Isi kredensial Wi-Fi dan Telegram pada kode ESP8266.
4. Unggah telegram_alert.ino ke NodeMCU ESP8266.
5. Uji sistem dengan objek pada jarak yang ditentukan.

## Catatan
- Ambang deteksi awal: 50 cm.
- Sesuaikan ambang dengan kebutuhan dan kondisi ruangan.
- Sistem mendeteksi objek, bukan memastikan bahwa objek
  tersebut adalah maling.
- Jangan publikasikan token bot atau kata sandi Wi-Fi.
- Periksa wiring dan tegangan sebelum menyalakan perangkat.

## Status
Prototipe pembelajaran IoT.
# Kelompok 6 -KSiX
