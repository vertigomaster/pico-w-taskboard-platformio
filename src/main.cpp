#include <Arduino.h>
#include <PicoDiagnostics.h>
#include <TaskRow.h>

//note: arduino framework wraps most of this already - it handles the wifi, for example. do not touch cyw43 directly
// #include "pico/stdlib.h"
// #include "pico/cyw43_arch.h"

#define BEEPER_PIN 13u
#define TEST_LED 14u
#define TEST_BUTTON 12u

void setup() {
  //some magic number idk; 
  //it should keep the USB in listening mode to make uploads easier
  Serial.begin(115200); 

  // put your setup code here, to run once:
  //apparently philehower is handling the Wifi instead of the pico core
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);

  pinMode(TEST_LED, OUTPUT);
  pinMode(TEST_BUTTON, INPUT_PULLDOWN);
  pinMode(BEEPER_PIN, OUTPUT);

  Serial.println("Setup complete");
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(1);
}