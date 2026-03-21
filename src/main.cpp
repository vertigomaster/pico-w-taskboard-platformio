#include <Arduino.h>
#include <PicoDiagnostics.h>
#include <ITaskRow.h>
#include <GPIOImpl/GPIOTaskRow.h>
#include "taskboard.h"
#include <LittleFS.h>
#include "lafvin_devkit.h"

// note: arduino framework wraps most of this already - it handles the wifi, for example. 
//do not touch cyw43 directly
//  #include "pico/stdlib.h"
//  #include "pico/cyw43_arch.h"


#define FORMAT_LITTLEFS_IF_FAILED false

void dev_turnOnFatalRuntimeErrorLight()
{
#ifdef DEV_USING_LAFVIN_BREAKOUT_BOARD
    pinMode(DEVBOARD_ERROR_LED_PIN, OUTPUT);
    digitalWrite(DEVBOARD_ERROR_LED_PIN, HIGH);
#endif
}

void setup()
{
    // Keeps the USB in listening mode, enables remotely flashing, which makes uploads easier, speeding up our dev cycles
    //the number (the "baudrate") doesn't actually matter, apparently - unless doing other specific things.
    Serial.begin(115200);
    Serial.println("Waiting 500ms to ensure serial connection established...");
    delay(500);

#ifdef RUN_DIAGNOSTICS
    Serial.println("Diagnostic Pin Output Test");
    PicoDiagnostics::SetAllGPIOsOutHigh();
#ifdef DEV_USING_LAFVIN_BREAKOUT_BOARD
    digitalWrite(DEVBOARD_BEEPER_PIN, LOW);
#endif
    // return;
    delay(4000);
    PicoDiagnostics::SetAllGPIOsOutLow();
    Serial.println("Finished Diagnostic Pin Output Test");
#endif

    Serial.println("Beginning Setup...");

    Serial.println("Setting up dev beeper...");
    if(Beep::Setup()){
        Serial.println("Beeper Set Up!");
    } else {
        Serial.println("WARNING: Beeper not set up. No Beep SFX configured.");
    }

    Serial.println("Setting up File System...");
    if(LittleFS.begin()){
        Serial.println("File System Set Up!");
    } else {
        dev_turnOnFatalRuntimeErrorLight();
        Serial.println("FATAL ERROR: File System setup failed - cannot read/write task data :(");
        return;
    }

    Serial.println("Setting up Taskboard module...");
    int taskboardSetupCode = Taskboard::Setup(&LittleFS);
    if(taskboardSetupCode != 0){
        dev_turnOnFatalRuntimeErrorLight();
        Serial.printf("FATAL ERROR: Taskboard Module hit error code %d!", taskboardSetupCode);
        return;
    } else {
        Serial.println("Taskboard Module Set Up!");
    }
    
    Taskboard::MakeReadyBeepSound();
    Serial.println("Setup Complete!");
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, HIGH);
}

void loop()
{
    Taskboard::RunRowCheckLoop();
    delay(10);
}