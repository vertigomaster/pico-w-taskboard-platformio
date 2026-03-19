#pragma once
#include <Arduino.h>
#include <PicoDiagnostics.h>
#include <ITaskRow.h>
#include <GPIOImpl/GPIOTaskRow.h>

#define BEEPER_PIN 13u

using ITaskRow = TactileTaskBoard::ITaskRow;
using GPIORow = TactileTaskBoard::GPIOTaskRow;

ITaskRow* NewTestRowAsGPIO(pin_size_t buttPin, pin_size_t ledPin);
void SetUpTaskboard();
void RunRowCheckLoop();