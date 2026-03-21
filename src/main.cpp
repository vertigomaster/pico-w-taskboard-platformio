#include <Arduino.h>
#include <PicoDiagnostics.h>
#include <ITaskRow.h>
#include <GPIOImpl/GPIOTaskRow.h>
#include "taskboard.h"
#include <LittleFS.h>

// note: arduino framework wraps most of this already - it handles the wifi, for example. 
//do not touch cyw43 directly
//  #include "pico/stdlib.h"
//  #include "pico/cyw43_arch.h"

// #define TEST_LED 14u
// #define TEST_BUTTON 12u
#define FORMAT_LITTLEFS_IF_FAILED false


void setup()
{
    // Keeps the USB in listening mode, enables remotely flashing, which makes uploads easier, speeding up our dev cycles
    //the number (the "baudrate") doesn't actually matter, apparently - unless doing other specific things.
    Serial.begin(115200);
    delay(100);
    Serial.println("Beginning Setup...");

    Serial.println("Setting up File System...");
    if(LittleFS.begin()){
        Serial.println("File System Set Up!");
    } else {
        Serial.println("File System setup failed - cannot read/write task data :(");
        return;
    }

    Serial.println("Setting up Taskboard module...");
    SetUpTaskboard(*LittleFS);
    Serial.println("Taskboard Module Set Up!");
    
    Serial.println("Setup Complete!");
    digitalWrite(LED_BUILTIN, HIGH);
}

void loop()
{
    RunRowCheckLoop();
    delay(10);
}