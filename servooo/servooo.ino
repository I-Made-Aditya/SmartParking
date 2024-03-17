
#include <ESP32Servo.h>

#define SERVO_PIN 13 // ESP32 pin GIOP26 connected to servo motor

Servo servoMotor;

void setup() {
  servoMotor.attach(SERVO_PIN);  // attaches the servo on ESP32 pin
  servoMotor.write(0);
  servoMotor.write(95);
  servoMotor.write(0);
}

void loop() {
  
//  delay(1000);
  
//  delay(1000);
//  servoMotor.write(0);
//  delay(3000);
//  servoMotor.write(79);
//  delay(500);

// for(int pos = 90; pos < 100; pos += 1){
//    myservo.write(pos); //prosedur penulisan data PWM ke motor servo
//    delay(15); //waktu tunda 15 ms                 
// } 
// for(int pos = 100; pos>=89; pos-=1){                              
//    myservo.write(pos);                 
//    delay(15);                         
// }
// for(int pos = 90; pos>=79; pos-=1){                              
//    myservo.write(pos);                 
//    delay(15);                        
// }
 
  
//  servoMotor.write(90);
//  delay(2000);
}
