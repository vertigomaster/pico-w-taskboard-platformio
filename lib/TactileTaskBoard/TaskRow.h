#pragma once
#include <Arduino.h>

namespace TactileTaskBoard {
    void OnButtonPressWrapper_GPIO(TactileTaskBoard::GPIOTaskRow* row);
    void OnButtonReleaseWrapper_GPIO(TactileTaskBoard::GPIOTaskRow* row);

    //class for task element
    class TaskRow {
        public:
        uint32_t taskID;

        virtual void Setup() = 0;
        ~TaskRow() = default;
    };

    class GPIOTaskRow : public TaskRow {
        public:
        GPIOTaskRow(pin_size_t buttonPin, pin_size_t ledPin) : _gpioButtonPin(buttonPin), _gpioLedPin(ledPin) {}

        void Setup() override;
        void AttachInterrupt();

        //press/release 
        void InterruptCallback_OnButtonPress();
        void InterruptCallback_OnButtonRelease();

        void TurnOnLED();
        void TurnOffLED();

        private:
        pin_size_t _gpioButtonPin;
        pin_size_t _gpioLedPin;
        volatile bool _pressed = false;
    };

    class I2CTaskRow : public TaskRow {
        void Setup() override;
    };
}