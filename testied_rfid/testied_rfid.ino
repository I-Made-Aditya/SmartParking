byte sda = 21;
byte rst = 22;
#include<KRrfid.h>

void setup() {
  Serial.begin(9600);
  rfidBegin();
}

void loop() {
  getTAG();
  if (TAG != "") {
    Serial.print("TAG :");
    Serial.println(TAG);
    TAG = "";
  }
}
