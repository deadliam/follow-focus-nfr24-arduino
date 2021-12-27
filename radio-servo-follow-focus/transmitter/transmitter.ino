//Adding Libraries 

#include <SPI.h>                  /* to handle the communication interface with the modem*/
#include <nRF24L01.h>             /* to handle this particular modem driver*/
#include <RF24.h>                 /* the library which helps us to control the radio modem*/

#define pot_pin A0                /*Variable pin of POT is to be connected to analog pin 0 i.e.A0*/
RF24 radio(7,8);                    /* Creating instance 'radio'  ( CE , CSN )   CE -> D7 | CSN -> D8 */                              
const byte Address[6] = "00009" ;     /* Address to which data to be transmitted*/

const int button1Pin = 2;
const int button2Pin = 3;
const int button3Pin = 4;
const int switch1Pin = 5;

int button1State = 0;
int button2State = 0;
int button3State = 0;
int switch1State = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(pot_pin,INPUT);          /* Setting A0 (POT pin) as input*/
  radio.begin();                   /* Activate the modem*/
  radio.openWritingPipe (Address); /* Sets the address of transmitter to which program will send the data */
  pinMode(button1Pin, INPUT);
  pinMode(button2Pin, INPUT);
  pinMode(button3Pin, INPUT);
  pinMode(switch1Pin, INPUT);
}
void loop() {

  button1State = digitalRead(button1Pin);
  button2State = digitalRead(button2Pin);
  button3State = digitalRead(button3Pin);
  switch1State = digitalRead(switch1Pin);
  
  // put your main code here, to run repeatedly:
  radio.stopListening();          /* Setting modem in transmission mode*/
  int value = analogRead(pot_pin);    /*Reading analog value at pin A0 and storing in varible 'value'*/
  int data = map( value , 0 , 1023 , 0 , 180 );   /* Convering the 10 bit value to 8 bit */
  radio.write(&data, sizeof(data));            /* Sending data over NRF 24L01*/
  Serial.print("Transmitting Data : ");
  Serial.println(data);                           /* Printing POT value on serial monitor*/
} 
