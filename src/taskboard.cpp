#include "taskboard.h"

//TODO: look into c++ array syntax
ITaskRow* row1 = nullptr;
ITaskRow* row2 = nullptr;

ITaskRow* NewTestRowAsGPIO(pin_size_t buttPin, pin_size_t ledPin) 
{
    GPIORow* newRow = new GPIORow(buttPin, ledPin);

    digitalWrite(BEEPER_PIN, HIGH);
    delay(10);
    digitalWrite(BEEPER_PIN, LOW);
    delay(50);
    digitalWrite(BEEPER_PIN, HIGH);
    delay(10);
    digitalWrite(BEEPER_PIN, LOW);
    delay(100);
    return newRow;
}

void SetUpTaskboard()
{
    pinMode(LED_BUILTIN, OUTPUT);
    pinMode(BEEPER_PIN, OUTPUT);

    row1 = NewTestRowAsGPIO(12,14);
    row2 = NewTestRowAsGPIO(18,15);
    row1->Setup();
    row2->Setup();
}

void RunRowCheckLoop() {
    //dirty check to see if any new changes have occured
    if (row1 != nullptr && row1->IsDirty())
    {
        row1->Refresh();
        
        Serial.println("Button state changes detected. Took clean snapshot.");
        //check if all completed

        //if snapshot shows it was pressed, kick off a beep
        if (row1->IsPressed_Clean()) {
            Serial.printf("Snapshot shows button 1 was just pressed.\n");
        } else { 
            Serial.printf("Snapshot shows button 1 was just released.\n");
        }
    }

    //dirty check to see if any new changes have occured
    if (row2 != nullptr && row2->IsDirty())
    {
        row2->Refresh();
        
        Serial.println("Button state changes detected. Took clean snapshot.");
        //check if all completed

        //if snapshot shows it was pressed, kick off a beep
        if (row2->IsPressed_Clean()) {
            Serial.printf("Snapshot shows button 2 was just pressed.\n");
        } else { 
            Serial.printf("Snapshot shows button 2 was just released.\n");
        }
    }
}