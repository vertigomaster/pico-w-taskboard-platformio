#pragma once
#include <Arduino.h>
#include <PicoDiagnostics.h>
#include <ITaskRow.h>
#include <GPIOImpl/GPIOTaskRow.h>
#include <LittleFS.h>
#include "lafvin_devkit.h"
#include "buzzer_sfx.h"

namespace Taskboard { 

    using ITaskRow = TactileTaskBoard::ITaskRow;
    using GPIORow = TactileTaskBoard::GPIOTaskRow;

    ITaskRow* NewTestRowAsGPIO(pin_size_t buttPin, pin_size_t ledPin);
    //retrieve externally, as may need to share it with other modules
    int Setup(FS* fileSysPtr);//, int maxTaskCount);
    int RunRowCheckLoop();

    bool RefreshRow(ITaskRow *rowPtr, size_t index);

    void MakeReadyBeepSound();
}