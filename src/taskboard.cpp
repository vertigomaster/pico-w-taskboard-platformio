#include "taskboard.h"

namespace Taskboard
{
#define SUCCESSCODE 0
#define ERRORCODE_NOT_SET_UP 1
#define ERRORCODE_BAD_TASK_ROW_COUNT 2

#define PHYSICAL_TASKROW_COUNT 16
#define FOR_EACH_ROW(index) for (size_t i = 0; index < maxTaskCount; index++)

    GPIORow rows[PHYSICAL_TASKROW_COUNT];

    FS *activeFileSysPtr;
    int maxTaskCount;
    bool taskboardSetupCompleted = false;
    bool celebrated = false;

    // ITaskRow *NewTestRowAsGPIO(pin_size_t buttPin, pin_size_t ledPin)
    // {
    //     GPIORow *newRow = new GPIORow(buttPin, ledPin);
    //     MakeReadyBeepSound();
    //     return newRow;
    // }

    int Setup(FS *fileSysPtr) //, int totalTaskCount
    {
        // need something better soon,
        // maybe pull from server or have a config/setup mode?
        maxTaskCount = 2;
        if (maxTaskCount < 1 || maxTaskCount > PHYSICAL_TASKROW_COUNT)
        {
            // scream
            // TODO: find error thing
            return ERRORCODE_BAD_TASK_ROW_COUNT;
        }

        // need something better soon,
        // maybe pull from server or have a config/setup mode?
        rows[0].Begin(12, 14);
        Beep::ElementSetup();
        rows[1].Begin(18, 15);
        Beep::ElementSetup();

        activeFileSysPtr = fileSysPtr;
        taskboardSetupCompleted = true;
        return 0;
    }

    int RunRowCheckLoop()
    {
        if (!taskboardSetupCompleted)
            return ERRORCODE_NOT_SET_UP;

        // refresh all row states to see if any changes occured
        bool changeDetected = false;
        FOR_EACH_ROW(i)
        {
            if (RefreshRow(&rows[i], i))
            {
                changeDetected = true;
            }
        }

        if (!changeDetected)
            return 0;

        Beep::Up3Notes();

        // verify if all tasks are complete
        bool allComplete = true;
        FOR_EACH_ROW(i)
        {
            if (!rows[i].IsTaskComplete())
            {
                allComplete = false;
                break;
            }
        }

        if (!allComplete)
        {
            celebrated = false;
            return 0;
        }

        if (!celebrated)
        {
            // all tasks complete!
            Serial.println("All Tasks Complete! Victory screech!");
            // do celebration

            // beep (for now)
            // TODO: do something cooler
            // digitalWrite(LED_BUILTIN, HIGH);
            // delay(500);
            // digitalWrite(LED_BUILTIN, LOW);
            Beep::Yay();

            celebrated = true;

            Serial.println("Resetting tasks (temp)");
            // reset completion states (temp, want to see it's working)
            // later they should stay complete until explicitly reset
            FOR_EACH_ROW(i)
            {
                rows[i].MarkTaskComplete(false);
            }
        }

        return 0;
    }

    bool RefreshRow(ITaskRow *rowPtr, size_t index)
    {
        if (!rowPtr->IsDirty())
            return false;

        rowPtr->Refresh();

        Serial.println("Button state changes detected. Took clean snapshot.");
        // check if all completed

        // if snapshot shows it was pressed, kick off a beep
        if (rowPtr->IsTaskComplete())
        {
            Serial.printf("Task %d now complete!\n", index);
        }
        else
        {
            Serial.printf("Snapshot shows Task #%d no longer complete.\n", index);
        }

        return true;
    }

    void MakeReadyBeepSound() { Beep::AllSystemsGo(); }
}