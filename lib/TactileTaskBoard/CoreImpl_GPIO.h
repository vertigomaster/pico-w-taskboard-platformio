#pragma once
#include <CoreInterfaces.h>
#include <Arduino.h>

namespace TactileTaskBoard {
    class GPIOTaskButton : public ITaskButton {
        public:
        GPIOTaskButton(pin_size_t pin) : _gpioPin(pin) {}

        void Setup() override;
        void AttachInterrupt() override;

        void OnButtonPress();

        private:
        pin_size_t _gpioPin;
        volatile bool _pressed = false;

        
    };

    class GPIOTaskLED : public ITaskLED {
        public:
        void TurnOn() override;
        void TurnOff() override;
        bool IsOn() override;
    };
}