#include <Arduino.h>
#include <PicoDiagnostics.h>
#include <ITaskRow.h>
#include <GPIOImpl/GPIOTaskRow.h>

using ITaskRow = TactileTaskBoard::ITaskRow;
using GPIORow = TactileTaskBoard::GPIOTaskRow;

// note: arduino framework wraps most of this already - it handles the wifi, for example. 
//do not touch cyw43 directly
//  #include "pico/stdlib.h"
//  #include "pico/cyw43_arch.h"

// #define DEBUG_MODE

#define BEEPER_PIN 13u
#define TEST_LED 14u
#define TEST_BUTTON 12u

ITaskRow* testRow = nullptr;

ITaskRow* NewTestRowAsGPIO() 
{
    GPIORow* newRow = new GPIORow(TEST_BUTTON, TEST_LED);

    // #ifdef DEBUG_MODE
    // Serial.printf("New GPIOTaskRow set up with button pin GP%d and led pin GP%d\n", 
    //     newRow->gpioButtonPin, newRow->gpioLedPin);
    // #endif

    return newRow;
}

void setup()
{
    // #ifdef DEBUG_MODE
    Serial.println("Beginning Setup...");
    // #endif

    // Keeps the USB in listening mode, enables remotely flashing, which makes uploads easier, speeding up our dev cycles
    //the number (the "baudrate") doesn't actually matter, apparently - unless doing other specific things.
    Serial.begin(115200);

    testRow = NewTestRowAsGPIO();
    testRow->Setup();

    pinMode(BEEPER_PIN, OUTPUT);

    // #ifdef DEBUG_MODE
    Serial.println("Setup Complete!");
    // #endif
}

void loop()
{
    //dirty check to see if any new changes have occured
    if (testRow->IsDirty())
    {
        //Later on we could have it return a snapshot object instead; a bit overkill for a hobby project, but would make the library easier to use.
        testRow->TakeCleanStateSnapshot(); //caches and marks
        //the raw state is now ready to await new changes

        Serial.println("Button state changes detected. Took clean snapshot.");

        //if snapshot shows it was pressed, kick off a beep
        if (testRow->IsPressed_Clean())
        {
            Serial.println("Snapshot shows button was just pressed.");

            digitalWrite(BEEPER_PIN, HIGH);
            delay(100); //interrupts will still jump in, but the beep needs to continue
        }
        else//otherwise, snapshot says it is not pressed. since it was dirtied, we know this is a change, and thus turn it off.
        {
            Serial.println("Snapshot shows button was just released.");
            digitalWrite(BEEPER_PIN, LOW);
        }
    }
}