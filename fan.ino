//the transistor which controls the motor will be attached to digital pin 9
const int motorControl = 3;
//The pin for the potenciometer
const int pinPot = A0;
//current tempeture taken from sensor
const int tempPin = A1;
//the pin for button changing between C and F
const int CFPin = 4;
//bool used to keep trak of current metric used
bool IsC = true;

#include <LiquidCrystal.h>
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);
// the setup routine runs once when you press reset:

void setup() {
  lcd.begin(16, 2);
  
  // make the potenciometurs's pin an input:
  pinMode(pinPot, INPUT);

  // make the transistor's pin an output:
  pinMode(motorControl, OUTPUT);  
  
  // make the tempetur sensor's pin an output:
  pinMode(tempPin, INPUT);
  
  //enables the serial monitor
  Serial.begin(9600);
  
  pinMode(CFPin, INPUT);
}

// the loop routine runs over and over again forever:
void loop() {
  int reading = analogRead(tempPin);
  //Serial.println(reading);
  float voltage = reading * 5.0;
  voltage /= 1024.0; 
  lcd.setCursor(0, 0);
  String messegeTemp = "Temp: ";
  if(digitalRead(CFPin) != HIGH)
  {
    messegeTemp += calcC(voltage);
    messegeTemp += "C    ";
  }
  else
  {
     messegeTemp += (calcC(voltage) * 9.0 / 5.0) + 32.0;
     messegeTemp += "F    ";
  }
  lcd.print(messegeTemp);
  //gets and displays temp
  
  //gets pinpot val and turns into readable num
  int analogVal = analogRead(pinPot);
  //gets potenciometer value from 1023 to 0
  analogWrite(motorControl, map(analogVal, 0, 1023, 0, 255));
  //turns it from 1023-0 to 255-0 
  //gives it to the npn that runs the motor
  String messegeRPM = "Fan: ";
  messegeRPM += map(analogVal, 0, 1023, 0, 100);
  //map to get value for lcd
  messegeRPM += "%       ";
  //can't clear line or chars this fixes ghosting 
  lcd.setCursor(0, 1);
  //sets cursur to second line
  lcd.print(messegeRPM);
  

  delay(1);        // delay for stability
}

float calcC(float voltage)
{
  return (voltage - 0.5) * 100;
}
