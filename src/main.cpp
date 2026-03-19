#include <Arduino.h>
#include <PicoDiagnostics.h>
#include <ITaskRow.h>
#include <GPIOImpl/GPIOTaskRow.h>
#include "taskboard.h"

// note: arduino framework wraps most of this already - it handles the wifi, for example. 
//do not touch cyw43 directly
//  #include "pico/stdlib.h"
//  #include "pico/cyw43_arch.h"

// #define TEST_LED 14u
// #define TEST_BUTTON 12u


void setup()
{
    // Keeps the USB in listening mode, enables remotely flashing, which makes uploads easier, speeding up our dev cycles
    //the number (the "baudrate") doesn't actually matter, apparently - unless doing other specific things.
    Serial.begin(115200);
    delay(100);
    Serial.println("Beginning Setup...");

    SetUpTaskboard();
    // PicoDiagnostics::SetAllGPIOsOutHigh();
    // digitalWrite(BEEPER_PIN, LOW);
    
    Serial.println("Setup Complete!");
    digitalWrite(LED_BUILTIN, HIGH);
}

void loop()
{
    RunRowCheckLoop();
    delay(10);
}