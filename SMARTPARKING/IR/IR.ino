//int ledPin = 15; // choose pin for the LED
int inputPin = 14; // choose input pin (for Infrared sensor) 
int val = 0; // variable for reading the pin status

void setup() 
{ 
  Serial.begin(115200);
//   pinMode(ledPin, OUTPUT); // declare LED as output 
   pinMode(inputPin, INPUT); // declare Infrared sensor as input
}

void loop()
{ 
//   val = digitalRead(inputPin); // read input value 
   Serial.println(digitalRead(inputPin));
   /*if (val == HIGH)
   { 
      Serial.println("Not Ditect");
      delay(500);
   } 
   else 
   { 
      Serial.println("Ditect");
      delay(500);
   } */
}
