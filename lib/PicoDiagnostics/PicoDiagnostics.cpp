#include "PicoDiagnostics.h"

namespace PicoDiagnostics
{
    uint32_t RunTestOnAllGPIOs(std::function<bool(pin_size_t)> pinTestImpl)
    {
        uint32_t pinTestResultsBitmask = 0;

        for (pin_size_t i = 0; i < PINS_COUNT; i++)
        {
            if (pinTestImpl(i))
            {
                pinTestResultsBitmask |= 1 << i;
            }
        }

        return pinTestResultsBitmask;
    }

    void SetAllGPIOsOutHigh()
    {
        RunTestOnAllGPIOs([](pin_size_t pinNumber){
            pinMode(pinNumber, OUTPUT);
            digitalWrite(pinNumber, HIGH);

            return true;
        });
    }

    uint32_t RunStandardTestsOnAllGPIOs()
    {
        uint32_t pendingResult;
        pendingResult = RunTestOnAllGPIOs(TestGPIOPin_VoltageShorts);
        pendingResult &= RunTestOnAllGPIOs(TestGPIOPin_GroundShorts);
        pendingResult &= RunTestOnAllGPIOs(TestGPIOPin_Bridges);
        return pendingResult;
    }

    // init Input with pulldown, value should be 0 when not actively in use.
    // If fails, pin likely shorted to voltage rail (3.3v)
    bool TestGPIOPin_VoltageShorts(pin_size_t pinNumber)
    {
        pinMode(pinNumber, INPUT_PULLDOWN);
        return digitalRead(pinNumber) == 0;
    }

    // init input with pull up, should read 1 when not actively in use.
    // If fails, pin likely shorted to ground
    bool TestGPIOPin_GroundShorts(pin_size_t pinNumber)
    {
        pinMode(pinNumber, INPUT_PULLUP);
        return digitalRead(pinNumber) == 1;
    }

    // tests for bridges between this pin and all others (except itself)
    // by setting this one to high and seeing what other pins read as high
    bool TestGPIOPin_Bridges(pin_size_t pinNumber)
    {
        pinMode(pinNumber, OUTPUT);
        digitalWrite(pinNumber, HIGH);

        for (pin_size_t i = 0; i < PINS_COUNT; i++)
        {
            if (i == pinNumber)
                continue;
            pinMode(i, INPUT_PULLDOWN);
            digitalRead(i);
        }

        return false;
    }
}