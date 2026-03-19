#pragma once
#include <Arduino.h>
#include "CoreInterfaces.h"


namespace TactileTaskBoard {
    void OnButtonPressWrapper_GPIO(TactileTaskBoard::GPIOTaskRow* row);

    //class for task element
    class TaskRow {
        public:
        uint32_t taskID;

        virtual void Setup() = 0;
        ~TaskRow() = default;
    };

    class GPIOTaskRow : public TaskRow {
        public:
        GPIOTaskRow(pin_size_t pin) : _gpioButtonPin(pin) {}
        void Setup() override;

        void AttachInterrupt();
        void OnButtonPress();

        private:
        pin_size_t _gpioButtonPin;
        volatile bool _pressed = false;
    };

    class I2CTaskRow : public TaskRow {
        void Setup() override;
    };
}