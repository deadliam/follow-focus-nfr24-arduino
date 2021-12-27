//// Adding Libraries 
#include <SPI.h>             /* to handle the communication interface with the modem*/
#include <nRF24L01.h>        /* to handle this particular modem driver*/
#include <RF24.h>            /* the library which helps us to control the radio modem*/
#include <Servo.h>
// https://github.com/guillaume-rico/SharpIR
#include <SharpIR.h>

RF24 radio(7,8);             /* Creating instance 'radio'  ( CE , CSN )   CE -> D7 | CSN -> D8 */                               
const byte Address[6] = "00009"; /* Address from which data to be received */
Servo myservo;
int Servo_value;
int Pev_servo_value;

// Define model and input pin:
#define IRPin A2
#define model 100500

// Create variable to store the distance:
int distance_cm; 
SharpIR mySensor = SharpIR(IRPin, model);

void setup() {
// put your setup code here, to run once:
  Serial.begin(9600);            /*Setting baudrate of Serial Port to 9600*/
  radio.begin();                   /* Activate the modem*/
  radio.openReadingPipe(1, Address); /* Sets the address of receiver from which program will receive the data*/
  myservo.attach(6);
  Serial.println("Loaded");
}

void loop() {
// put your main code here, to run repeatedly:
  radio.startListening();          /*Setting modem in Receiver mode*/
  Pev_servo_value = Servo_value;
  
//  distance_cm = mySensor.distance();
//  Serial.print("Mean distance: ");
//  Serial.print(distance_cm);
//  Serial.println(" cm");
//  delay(500);
  
  if (radio.available())
  {
    while (radio.available())              /* Loop until receiving valid data*/
    {
      int rx_data = 0 ;                    /* Variable to store received data */
      radio.read(&rx_data, sizeof(rx_data));/* Read the received data and store in ' rx_data ' */
      Serial.print("Received Data : ");
      Serial.println(rx_data);           /* Print received value on Serial Monitor */
//      analogWrite(led_pin , rx_data);/* Write received value to PWM pin 3 to which LED is connected */
      myservo.write(rx_data);
    }
  } else
    {
//      Serial.println("Not Receiving !!!"); /* If not receiving valid data print " Not Receiving !!! " on Serial Monitor  */
    }
  ///// END OF LOOP //////
}
