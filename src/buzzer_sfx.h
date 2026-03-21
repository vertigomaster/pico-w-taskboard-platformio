#pragma once
#include "lafvin_devkit.h"
#include <Arduino.h>

namespace Beep {

    //scientific scale in Hz
    #define NOTE_C4 262
    #define NOTE_D4 294
    #define NOTE_E4 323
    #define NOTE_F4 349
    #define NOTE_G4 392
    #define NOTE_A4 440
    #define NOTE_B4 494

    #define NOTE_MIDDLE_C NOTE_C4
    
    bool Setup();
    void Yay();
    void Up3Notes();
    void ElementSetup();
    void AllSystemsGo();
}