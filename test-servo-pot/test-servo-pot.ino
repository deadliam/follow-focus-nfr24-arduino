#include <Servo.h>  // add servo library
 
Servo myservo;  // create servo object to control a servo
 
int potpin = 0;  // analog pin used to connect the potentiometer
int val = 90;    // variable to read the value from the analog pin
int threshold = 90;

void setup() {
  Serial.begin(9600);
  myservo.attach(6);
  myservo.writeMicroseconds(1500);
}
 
void loop() {
  val = analogRead(potpin);            // reads the value of the potentiometer (value between 0 and 1023)
  val = map(val, 0, 1023, 0, 180);     // scale it to use it with the servo (value between 0 and 180)

//  if (val > threshold + 2 || val < threshold - 2) {
    if (val > 0 && val < 180) {
      myservo.write(val);                  // sets the servo position according to the scaled value
      threshold = val;
      Serial.println(val);
    }
//  }
  
  delay(15);                           // waits for the servo to get there
}
