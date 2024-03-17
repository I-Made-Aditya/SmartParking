#include <SPI.h>
#include <Wire.h> 
#include <MFRC522.h>
#include <ESP32Servo.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

#define RST_PIN 33
#define SDA_PIN 5
#define Buzzer 12
#define IR 14

int val=0;
Servo myservo;

MFRC522 mfrc522(SDA_PIN, RST_PIN);
// Replace with your network credentials (STATION)
const char* ssid = "WS Clown Project 2.4G";
const char* password = "membadutbersama";

String serverName = "http://parkir.sitesxyz.my.id/";

unsigned long lastTime = 0;
unsigned long timerDelay = 5000;


void setup() {
  Serial.begin(115200);
  SPI.begin();
  initWiFi();
  lcd.begin();
  lcd.backlight();
  myservo.attach(13);
  pinMode(IR, INPUT);
  pinMode(Buzzer, OUTPUT);
  mfrc522.PCD_Init();
  Serial.println("Put your card to the reader..."); 

}

void loop() {
  val = digitalRead(IR);
  if(val == HIGH){
    myservo.write(0);
  }
  delay(100);
 if(!mfrc522.PICC_IsNewCardPresent()){
    return;
  }

  if(!mfrc522.PICC_ReadCardSerial()){
    return;
  }

  Serial.print("UID tag :");
  String UID = "";

  for(byte i = 0; i < mfrc522.uid.size; i++){
    Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" :"");
    Serial.print(mfrc522.uid.uidByte[i], HEX);
    UID.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : ""));
    UID.concat(String(mfrc522.uid.uidByte[i], HEX));
  }

  Serial.println();
  Serial.print("Pesan : ");
  UID.toUpperCase();
  mfrc522.PICC_HaltA();
  mfrc522.PCD_StopCrypto1();

  HTTPClient http;
  String serverPath = serverName + "in.php?rfid=" + UID;
  http.begin(serverPath.c_str());
  int httpResponseCode = http.GET();

  if (httpResponseCode>0) {
      String payload = http.getString();
      if(payload == "0"){
        Serial.println("Kartu Tidak cocok / Anda Sudah Parkir");
        lcd.clear();
        lcd.setCursor(2, 0);
        lcd.print("Error !!!");
        digitalWrite(Buzzer, HIGH);
        delay(100);
        digitalWrite(Buzzer, LOW);
        delay(100);
      }else {
        Serial.println("SELAMAT DATANG"); 
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("SELAMAT DATANG");
        Serial.print("No Parkir : "); Serial.print(payload);
        lcd.setCursor(0, 1);
        lcd.print("No Parkir : "); lcd.print(payload);
        Serial.println("\n");
        digitalWrite(Buzzer, HIGH);
        delay(1000);
        digitalWrite(Buzzer, LOW);
        myservo.write(95);
        delay(3000);
      }
  }else {
      Serial.print("Error code: ");
      Serial.println(httpResponseCode);
  }
  http.end();

}

void initWiFi() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi ..");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(1000);
  }
  Serial.println(WiFi.localIP());
}
