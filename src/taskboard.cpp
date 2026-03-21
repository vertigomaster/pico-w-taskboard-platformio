#include "taskboard.h"

#define TASKROW_COUNT 16

GPIORow rows[TASKROW_COUNT];

FS* activeFileSysPtr;

void MakeReadyBeepSound()
{
    digitalWrite(BEEPER_PIN, HIGH);
    delay(20);
    digitalWrite(BEEPER_PIN, LOW);
    delay(50);
    digitalWrite(BEEPER_PIN, HIGH);
    delay(20);
    digitalWrite(BEEPER_PIN, LOW);
    delay(100);
}

ITaskRow* NewTestRowAsGPIO(pin_size_t buttPin, pin_size_t ledPin) 
{
    GPIORow* newRow = new GPIORow(buttPin, ledPin);
    MakeReadyBeepSound();
    return newRow;
}

void SetUpTaskboard(FS* fileSysPtr)
{
    activeFileSysPtr = fileSysPtr;

    pinMode(LED_BUILTIN, OUTPUT);
    pinMode(BEEPER_PIN, OUTPUT);

    for (size_t i = 0; i < TASKROW_COUNT; i++)
    {
        /* code */
    }
    
    rows[0].Begin(12,14);
    rows[1].Begin(18,15);
}

void RunRowCheckLoop() {
    //dirty check to see if any new changes have occured

    ITaskRow* rowPtr = nullptr;
    for (size_t i = 0; i < TASKROW_COUNT; i++)
    {
        rowPtr = &rows[i];
        if (rowPtr->IsDirty())
        {
            rowPtr->Refresh();
        
            Serial.println("Button state changes detected. Took clean snapshot.");
            //check if all completed

            //if snapshot shows it was pressed, kick off a beep
            if (rowPtr->IsPressed_Clean()) {
                Serial.printf("Snapshot shows button 1 was just pressed.\n");
            } else { 
                Serial.printf("Snapshot shows button 1 was just released.\n");
            }
        }
    }
}