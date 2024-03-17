#include <SPI.h>
#include <MFRC522.h>
#include <ESP32Servo.h>

#define RST_PIN 22
#define SDA_PIN 21
#define Buzzer 12

Servo myservo;

MFRC522 mfrc522(SDA_PIN, RST_PIN);


void setup() {
  Serial.begin(115200);
  SPI.begin();
  myservo.attach(13);
  pinMode(Buzzer, OUTPUT);
  mfrc522.PCD_Init();
  Serial.println("Put your card to the reader..."); 

}

void loop() {
  myservo.write(0);
  delay(100);
 if(!mfrc522.PICC_IsNewCardPresent()){
    return;
  }

  if(!mfrc522.PICC_ReadCardSerial()){
    return;
  }

  Serial.print("UID tag :");
  String content = "";
//  byte letter;

  for(byte i = 0; i < mfrc522.uid.size; i++){
    Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
    Serial.print(mfrc522.uid.uidByte[i], HEX);
    content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
    content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }

  Serial.println();
  Serial.print("Pesan : ");
  content.toUpperCase();

  if(content.substring(1) == "77 D6 8E 4A"){
    Serial.println("kartu cocok");
    Serial.println();
    digitalWrite(Buzzer, HIGH);
    myservo.write(95);
    delay(2000);
    digitalWrite(Buzzer, LOW);
  }

  else if(content.substring(1) == "3A AA F3 81"){
    Serial.println("kartu cocok");
    Serial.println();
    digitalWrite(Buzzer, HIGH);
    myservo.write(95);
    delay(2000);
    digitalWrite(Buzzer, LOW);
  }

  else{
    Serial.println("Kartu Tidak cocok");
    digitalWrite(Buzzer, HIGH);
    delay(100);
    digitalWrite(Buzzer, LOW);
    delay(100);
  }

}
