#pragma once
#include <ITaskRow.h>

namespace TactileTaskBoard
{
    class I2CTaskRow : public ITaskRow
    {
        public:
        //ITaskRow overrides
        void Begin() override;
        bool IsPressed_Raw() override;
        bool IsPressed_Clean() override;
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
