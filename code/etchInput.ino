/*
 * Johnny Krosby
 * 3/30/2022
 * 
 * Uses BasicEncoder to control two rotary encoders. 
 * Serial Prints all data so that Processing can read it and control the output.
 * This code is purely for the Input of the project.
 */

#include <Arduino.h>
#include <BasicEncoder.h>
#include <TimerOne.h>
 
BasicEncoder encoderA(10, 11);
BasicEncoder encoderB(7, 8);

int lastA, lastB;
int btnA = 6;
int btnB = 9;

int lastButtonPressA, lastButtonPressB;

void timer_service() {
  encoderA.service();
  encoderB.service();
}

void setup() {
  Serial.begin(9600);
  Timer1.initialize(1000);
  Timer1.attachInterrupt(timer_service);

  pinMode(btnA, INPUT);
  pinMode(btnB, INPUT);
}

void loop() {
  int encoder_a_change = encoderA.get_change();
  int encoder_b_change = encoderB.get_change();

  // Compare current count to last count to see in what direction it is moving.
  if(lastA != encoderA.get_count() || lastB != encoderB.get_count()){  
    if(encoderA.get_count() > lastA)
      Serial.println("X+");
    if(encoderA.get_count() < lastA)
      Serial.println("X-");

    if(encoderB.get_count() > lastB)
      Serial.println("Y+");
    if(encoderB.get_count() < lastB)
      Serial.println("Y-");
    
  /*
  Serial.print(lastA);
  Serial.print("  ");
  Serial.print(encoderA.get_count());
  Serial.println();
  Serial.print(lastB);
  Serial.print("  ");
  Serial.print(encoderB.get_count());
  Serial.println();
  */
  }
  
  lastA = encoderA.get_count();
  lastB = encoderB.get_count();

  // If the button is pressed, checks if it was pressed within 50ms. If not then print for Processing to read.
  if (!(digitalRead(btnA))) {         
    if (millis() - lastButtonPressA > 50)
      Serial.println("btnA");
    lastButtonPressA = millis();
  }
  
  if (!(digitalRead(btnB))) {
    if (millis() - lastButtonPressB > 50)
      Serial.println("btnB");
    lastButtonPressB = millis();
  }
}
