#include <SPI.h>
#include <MFRC522.h>

const int SS_PIN = 21;
const int RST_PIN = 22;

MFRC522 mfrc522(SS_PIN, RST_PIN);

void setup() {
  Serial.begin(115200);
  
  SPI.begin();
  mfrc522.PCD_Init();

  mfrc522.PCD_DumpVersionToSerial();
  Serial.print(F("Scan PICC to see UID, SAK, Type .."));
  

}

void loop() {
  if (!mfrc522.PICC_IsNewCardPresent() || !mfrc522.PICC_ReadCardSerial()){
    return;
  }

//  mfrc522.PICC_DumpToSerial(&(mfrc522.uid));
  String UID[2] = {"77D68E4A","3AAAF381"};

  Serial.print(F("Card UID : "));
  for(byte i = 0; i < mfrc522.uid.size; i++){
    UID[i] += (mfrc522.uid.uidByte[i] < 0x10 ? "0" : "") +
    String(mfrc522.uid.uidByte[i], HEX) + 
    + (i != (mfrc522.uid.size - 1) ? ":" : "");
  }

  UID.toUpperCase();
  Serial.println(UID);
  mfrc522.PICC_HaltA();
  
  for(int x=0; x<2; x++){
    if(UID[x]){
      Serial.println(UID[x])
      Serial.println("Kartu Terdeteksi");
    }
    else{
      Serial.println("Kartu Tidak Terdeteksi");
    }
  }
  delay(10);
}
