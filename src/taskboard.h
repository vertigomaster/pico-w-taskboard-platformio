#pragma once
#include <Arduino.h>
#include <PicoDiagnostics.h>
#include <ITaskRow.h>
#include <GPIOImpl/GPIOTaskRow.h>
#include <LittleFS.h>

#define BEEPER_PIN 13u

using ITaskRow = TactileTaskBoard::ITaskRow;
using GPIORow = TactileTaskBoard::GPIOTaskRow;

ITaskRow* NewTestRowAsGPIO(pin_size_t buttPin, pin_size_t ledPin);
//retrieve externally, as may need to share it with other modules
void SetUpTaskboard(FS* fileSysPtr); 
void RunRowCheckLoop();