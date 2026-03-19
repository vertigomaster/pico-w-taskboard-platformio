#include <Arduino.h>

//it seems these still work here!
// #include "pico/stdlib.h"
// #include "pico/cyw43_arch.h"

// put function declarations here:
int myFunction(int, int);
void OnTestButtonPressed();
void OnTestButtonReleased();
// int pico_led_init(void);
// void pico_set_led(bool led_on);

int result = myFunction(2,3);

// #define TEST_LED (19u)
#define BEEPER_PIN 13u //its the GP number?
#define TEST_LED 14u //its the GP number?
#define TEST_BUTTON 12u //its the GP number?
#define DEFAULT_RATE 0.1
#define MAX_BLINK_RATE 20.0

PinStatus testButtonState;
bool testButtonWasPressed = false;
float speed = DEFAULT_RATE;
bool lightOn = false;
bool toggledState = false;

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

  //TODO: learn how to do interrupts instead
  testButtonState = digitalRead(TEST_BUTTON);

  if(testButtonState == HIGH) {
    lightOn = true;
    // Serial.print("\r               ");
    // Serial.print("BUTTON HIGH");
    if(!testButtonWasPressed){
      testButtonWasPressed = true;
      //just pressed
      OnTestButtonPressed();
    }
    else {
      //being held down
    }
  } 
  else {
    lightOn = false;
    // Serial.print("\r               ");
    // Serial.print("BUTTON LOW");
    if(testButtonWasPressed){
      //just released
      testButtonWasPressed = false;
      OnTestButtonReleased();
    }
  }

  if(lightOn)
  {
    // digitalWrite(TEST_LED, HIGH);
  
    // // delay(0.5 * 1000.0 / speed);
    // delay(125);
  
    // // digitalWrite(LED_BUILTIN, LOW);
    // digitalWrite(TEST_LED, LOW);
  
    // // delay(0.5 * 1000.0 / speed);
    // delay(125);
  }

  delay(1);
  // Serial.print("\rHELLO WORLD I AM BLINKING!");
}

// put function definitions here:
int myFunction(int x, int y) {
  return x + y;
}

void OnTestButtonPressed(){
  Serial.println("\nTest Button just pressed");
  toggledState = !toggledState;
  digitalWrite(TEST_LED, toggledState ? HIGH : LOW);
  digitalWrite(BEEPER_PIN, HIGH);
  delay(50);
  digitalWrite(BEEPER_PIN, LOW);
}

void OnTestButtonReleased(){
  Serial.println("\nTest Button just released");
  // digitalWrite(TEST_LED, LOW);
}