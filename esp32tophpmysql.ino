#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <SPI.h>
#include <MFRC522.h>  // Library untuk modul RFID MFRC522


#define SDA_PIN 21  // Pin LCD 16x2
#define SCL_PIN 22 // Pin LCD 16x2 

#define SS_PIN 14 // Pin RFID
#define RST_PIN 27 // Pin RFID
MFRC522 mfrc522(SS_PIN, RST_PIN);
//         SDA(SS)      GPIO 14
//         SCK          GPIO 18
//         MOSI         GPIO 23
//         MISO         GPIO 19
//         IRQ          -
//         GND          GND
//         RST          GPIO 27
//         3.3V         3.3V

const char* ssid = "Pasti Dadi";
const char* password = "bejo0808";
const char* serverUrl = "http://192.168.116.154/telegram/kirimtelegram.php";

LiquidCrystal_I2C lcd(0x27, 16, 2);
#define buzzerPin 25  // Pin tempat buzzer terhubung
#define ledPin 2

void setup() {
  Serial.begin(115200);
    // Wire.begin();
  lcd.init();
  lcd.backlight();
  delay(10);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
    lcd.setCursor(0, 0);
    lcd.print("Connecting WiFi!");
  }
  Serial.println("Connected to WiFi");
  lcd.print("Connected");
  delay(1000);
  // lcd.clear();


  lcd.setCursor(0, 0);
  lcd.print("RFID Ready");

  pinMode(buzzerPin, OUTPUT);
  pinMode(ledPin, OUTPUT);

  SPI.begin();
  mfrc522.PCD_Init();
  Serial.println("RFID Ready");
}

void loop() {
  // lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Please scan RFID");

  digitalWrite(buzzerPin, LOW);
  digitalWrite(ledPin, LOW);

  if (!mfrc522.PICC_IsNewCardPresent() || !mfrc522.PICC_ReadCardSerial()) {

    return;
  }

  String rfidData = "";
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    rfidData += String(mfrc522.uid.uidByte[i], HEX);
  }
  rfidData.toUpperCase();

  mfrc522.PICC_HaltA();
  mfrc522.PCD_StopCrypto1();
  analogWrite(buzzerPin, 128);
  digitalWrite(ledPin, HIGH);  // Hidupkan LED
  delay(1000);                 // Bunyikan buzzer selama 500ms detik
  analogWrite(buzzerPin, 0);
  digitalWrite(ledPin, LOW);  // Matikan LED
  delay(1000);                // Tahan selama 500ms (setengah detik)
  sendDataToServer(rfidData);

  delay(1000);
}



bool sendDataToServer(String rfidData) {
  HTTPClient http;
  http.begin(serverUrl);
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");
  String postData = "{\"rfid\": \"" + rfidData + "\"}";
  // String postData = "rfid=" + rfidData;
  int httpResponseCode = http.POST(postData);
  String response = http.getString();
  Serial.println("Server response: " + response);

  if (response == "1") {
    Serial.println("terdaftar");
    lcd.begin(16, 2);  // Inisialisasi LCD
    lcd.print("  Tunggu!!!");
    lcd.setCursor(0, 1);
    lcd.print("    Kirim Data...");
    delay(1000);
    lcd.clear();
    Serial.println("  Terimakasih !! ");
    lcd.begin(16, 2);  // Inisialisasi LCD
    lcd.print("  Terimakasih");
    lcd.setCursor(0, 1);
    lcd.print("    Sudah Absen...");
    delay(1000);
  } else {
    Serial.println("belum terdaftar");
    lcd.begin(16, 2);  // Inisialisasi LCD
    lcd.print("  Kartu!");
    lcd.setCursor(0, 1);
    lcd.print("Belum Terdaftar.....");
  }
  if (httpResponseCode == 200) {
    String response = http.getString();
    lcd.clear();
    return response;

    http.end();
  } else {
    http.end();
    return false;
  }
}
