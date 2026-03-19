#pragma once
#include <ITaskRow.h>

namespace TactileTaskBoard
{
    class I2CTaskRow : public ITaskRow
    {
        public:
        //ITaskRow overrides
        void Setup() override;
        bool IsPressed() override;
        bool IsDirty() override;
        void TakeCleanStateSnapshot() override;
        void SetLEDState(bool shouldTurnOn) override;
        bool IsInputEnabled() override;
        void EnableInput(bool shouldEnableInput) override;

        private:
        //flag for input consumption
        //can't detact the interrupt, so this flag is just queried
        bool _isInputEnabled = false;
    };
}
