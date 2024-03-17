#include <SPI.h>
#include <MFRC522.h>
#include <ESP32Servo.h>
#include <WiFi.h>
#include <HTTPClient.h>


#define RST_PIN 33
#define SDA_PIN 21
#define Buzzer 12

#define IR 4

#define IR1 14
#define IR2 27
#define IR3 26
#define IR4 25
#define IR5 32
#define IR6 35


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
  myservo.attach(13);
  pinMode(IR, INPUT);
  pinMode(IR1, INPUT);
  pinMode(IR2, INPUT);
  pinMode(IR3, INPUT);
  pinMode(IR4, INPUT);
  pinMode(IR5, INPUT);
  pinMode(IR6, INPUT);
  pinMode(Buzzer, OUTPUT);
  mfrc522.PCD_Init();
  Serial.println("Put your card to the reader..."); 

}

void loop() {
  if ((millis() - lastTime) > timerDelay){
    bool ir1, ir2, ir3, ir4, ir5, ir6;
    ir1 = !digitalRead(IR1);
    ir2 = !digitalRead(IR2);
    ir3 = !digitalRead(IR3);
    ir4 = !digitalRead(IR4);
    ir5 = !digitalRead(IR5);
    ir6 = !digitalRead(IR6);
   
    HTTPClient http_map;
    String serverPath_map = serverName + "sensor.php?s1=" + ir1 + "&s2=" + ir2 + "&s3=" + ir3 + "&s4=" + ir4 + "&s5=" + ir5 +"&s6=" + ir6;  
    http_map.begin(serverPath_map.c_str());
    http_map.GET();
    
    lastTime = millis();
  }
  
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
  
  UID.replace(" ","");
  HTTPClient http;
  String serverPath = serverName + "out.php?rfid=" + UID;
  http.begin(serverPath.c_str());
  
  
  int httpResponseCode = http.GET();
  
  if (httpResponseCode>0) {
      String payload = http.getString();
      if(payload == "0"){
        Serial.println("Anda Sedang tdk parkir / Kartu tdk cocok");
        digitalWrite(Buzzer, HIGH);
        delay(100);
        digitalWrite(Buzzer, LOW);
        delay(100);
        }else if(payload == "1") {
        Serial.println("SELAMAT JALAN");
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
