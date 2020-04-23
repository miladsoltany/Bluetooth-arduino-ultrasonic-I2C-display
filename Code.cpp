#include <FastIO.h>
#include <I2CIO.h>
#include <LCD.h>
#include <LiquidCrystal.h>
//#include <LiquidCrystal_I2C.h>
#include <LiquidCrystal_SR.h>
#include <LiquidCrystal_SR2W.h>
#include <LiquidCrystal_SR3W.h>
#include "Wire.h" // For I2C
#include "LCD.h" // For LCD
#include "LiquidCrystal_I2C.h"
LiquidCrystal_I2C lcd(0x27,2,1,0,4,5,6,7); //Defining the Serial lcd

int soundSpeed = 340 //The normal sound speed is 340 m/s


const int VCC = 13;   // VCC pin for the sensor
const int VCC2 = 12;  //VCC pin for the BT


//set the delay
int del = 2000;  //The delay for displaying names
int updel = 300; //The delay for uodating the results


// defines pins numbers
const int trigPin = 9;  //The trigger pin
const int echoPin = 10; //The echo pin


// defines variables
long duration;  //The duration it takes for the wave to be transmitted and received
int distance;   //The distance between the object and the sensor

int BLVCC = 3;  //VCC for the BL
int BLGND = 8;  //Gnd for the BL





void setup() {
  //Setting the pin modes
  pinMode(VCC,OUTPUT);
  digitalWrite(VCC,HIGH);
  pinMode(VCC2,OUTPUT);
  digitalWrite(VCC2,HIGH);
  
  pinMode(BLVCC,OUTPUT);
  digitalWrite(BLVCC,HIGH);
  pinMode(BLGND,OUTPUT);
  digitalWrite(BLGND,LOW);
  
  lcd.setBacklightPin(3,POSITIVE); //The LCD backlight pin
  lcd.begin (16,2); //16 x 2 LCD module
  lcd.setBacklight(HIGH);  //Turning on the LCD backlight

  

  //Introduction and writing the names
  lcd.clear(); //Clear the screen
  lcd.home();  //returns the curser to (0,0) position
  lcd.print("Linear Algebra");
  lcd.setCursor(0,1); 
  lcd.print("Prof. Ebadollahi");
  delay(del);
  lcd.clear();
  lcd.home();
  lcd.print("Milad");
  lcd.setCursor(0,1);
  lcd.print("Soltany");
  delay(del);
  lcd.clear();
  lcd.home();
  lcd.print("AmirHossein");
  lcd.setCursor(0,1);
  lcd.print("Kazerooni");
  delay(del);
  lcd.clear();
  lcd.home();
  lcd.print("Amir");
  lcd.setCursor(0,1);
  lcd.print("Zahedi");
  delay(del);
  lcd.clear();


  //The trig pin is gonna send out a signal that's why it should be declared as output
  //and the echo pin is gonna be recieving signals, hence, input.
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  Serial.begin(9600); // Starts the serial communication at the baud rate of 9600
  

  
} //end of the main program




void loop() {
// Clears the trigPin
digitalWrite(trigPin, LOW);
delayMicroseconds(2);
// Sets the trigPin on HIGH state for 10 micro seconds
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);

// Reads the echoPin, returns the sound wave travel time in microseconds
duration = pulseIn(echoPin, HIGH); //the round trip of the sound in uS

// Calculating the distance
distance= duration*0.001 * soundSpeed/2;    //delta X = v * t  , v is the speed of sound
//The duration is in mS so we need a multiplification of 0.001 to convert it into seconds 
//The duration, hence the distance is for the round trip so we need to devide the results by a factor of 2

// Prints the distance on the Serial Monitor
lcd.print("Distance: ");
lcd.setCursor(0,1);
lcd.print(distance);
lcd.print("CM");
delay(updel);
lcd.clear();

Serial.print(distance);
Serial.println("CM\n\n\n");
}