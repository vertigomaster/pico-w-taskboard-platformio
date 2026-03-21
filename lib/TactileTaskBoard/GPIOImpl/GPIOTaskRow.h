#pragma once
#include <ITaskRow.h>

namespace TactileTaskBoard {
    class GPIOTaskRow : public ITaskRow {
        public:
        GPIOTaskRow(pin_size_t buttonPin, pin_size_t ledPin) 
            : gpioButtonPin(buttonPin), gpioLedPin(ledPin), _isReady(true) {}
        
        //post construction setup
        void Begin(pin_size_t buttonPin, pin_size_t ledPin)
        {
            gpioButtonPin = buttonPin;
            gpioLedPin = ledPin;
            _isReady = true;
        }

        //ITaskRow overrides
        void Begin() override;
        bool IsReady() override { return _isReady; }
        bool IsPressed_Raw() override;
        bool IsPressed_Clean() override;
        bool IsDirty() override;
        void TakeCleanStateSnapshot() override;
        void Refresh() override;
        void SetLEDState(bool shouldTurnOn) override;
        bool IsInputEnabled() override;
        void EnableInput(bool shouldEnableInput) override;
        
        pin_size_t gpioButtonPin;
        pin_size_t gpioLedPin;
        
        protected:        
        void AttachInterrupt();
        //press/release 
        void InterruptCallback_OnButtonChange();
        void InterruptCallback_OnButtonPress();
        void InterruptCallback_OnButtonRelease();
        static inline void OnButtonChangeWrapper(TactileTaskBoard::GPIOTaskRow* row){ row->InterruptCallback_OnButtonChange(); }
        // static inline void OnButtonPressWrapper(TactileTaskBoard::GPIOTaskRow* row){ row->InterruptCallback_OnButtonPress(); }
        // static inline void OnButtonReleaseWrapper(TactileTaskBoard::GPIOTaskRow* row){ row->InterruptCallback_OnButtonRelease(); }

        private:
        //flag for input consumption
        //can't detact the interrupt, so this flag is just queried
        bool _isInputEnabled = false;
        bool _isReady = false;
        
        volatile bool _pressedState_interrupt = false;
        volatile bool _isDirtyFlag = false;
        //to avoid collisions, only the interrupt writes to the volatile pressed boolean
        bool _pressedState_clean = false;
    };
}