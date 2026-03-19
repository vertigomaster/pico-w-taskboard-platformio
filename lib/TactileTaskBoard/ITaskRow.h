#pragma once
#include <Arduino.h>

namespace TactileTaskBoard {
    //not sure why this didn't work, moved it out of the namespace for now
    // void OnButtonPressWrapper_GPIO(TactileTaskBoard::GPIOTaskRow* row);
    // void OnButtonReleaseWrapper_GPIO(TactileTaskBoard::GPIOTaskRow* row);

    //class for task element
    class ITaskRow {
        public:
        uint32_t taskID;

        virtual void Setup() = 0;
        //abstracted since we'll migrate from direct GPIO pin reading to checking from an I2C expander

        //directly checks against the interrupt state, may flucuate
        virtual bool IsPressed_Raw() = 0;
        //checks against the snapshot of the cleaned state. Make sure you clean the object first to get up to date data
        virtual bool IsPressed_Clean() = 0;

        //has this row's current state been acknowledged (presumably by a monitoring system)?
        virtual bool IsDirty() = 0;


        //marks this row's current state as acknowledged (presumably by a monitoring system)
        virtual void TakeCleanStateSnapshot() = 0;
        virtual void Refresh() = 0;

        virtual void SetLEDState(bool shouldTurnOn) = 0;
        virtual bool IsInputEnabled() = 0;
        virtual void EnableInput(bool shouldEnableInput) = 0;

        inline bool IsTaskComplete() { return _taskCompleted; }
        virtual void MarkTaskComplete(bool doComplete);

        protected:
        bool _taskCompleted = false;

        ~ITaskRow() = default;
    };

}