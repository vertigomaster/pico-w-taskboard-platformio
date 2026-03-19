#include "PicoDiagnostics.h"

uint32_t PicoDiagnostics::RunTestOnAllGPIOs(std::function<bool(pin_size_t)> pinTestImpl)
{
    uint32_t pinTestResultsBitmask = 0;

    for (pin_size_t i = 0; i < PINS_COUNT; i++)
    {
        if(pinTestImpl(i)){
            pinTestResultsBitmask |= 1 << i;
        }
    }

    return pinTestResultsBitmask;
}

uint32_t PicoDiagnostics::RunStandardTestsOnAllGPIOs()
{
    uint32_t pendingResult;
    pendingResult = RunTestOnAllGPIOs(PicoDiagnostics::TestGPIOPin_VoltageShorts);
    pendingResult &= RunTestOnAllGPIOs(PicoDiagnostics::TestGPIOPin_GroundShorts);
    pendingResult &= RunTestOnAllGPIOs(PicoDiagnostics::TestGPIOPin_Bridges);
    return pendingResult;
}

//init Input with pulldown, value should be 0 when not actively in use.
//If fails, pin likely shorted to voltage rail (3.3v)
bool PicoDiagnostics::TestGPIOPin_VoltageShorts(pin_size_t pinNumber)
{
    pinMode(pinNumber, INPUT_PULLDOWN);
    return digitalRead(pinNumber) == 0;
}

//init input with pull up, should read 1 when not actively in use. 
//If fails, pin likely shorted to ground
bool PicoDiagnostics::TestGPIOPin_GroundShorts(pin_size_t pinNumber)
{
    pinMode(pinNumber, INPUT_PULLUP);
    return digitalRead(pinNumber) == 1;
}

//tests for bridges between this pin and all others (except itself) 
//by setting this one to high and seeing what other pins read as high
bool PicoDiagnostics::TestGPIOPin_Bridges(pin_size_t pinNumber)
{
    pinMode(pinNumber, OUTPUT);
    digitalWrite(pinNumber, HIGH);

    for (pin_size_t i = 0; i < PINS_COUNT; i++)
    {
        if(i == pinNumber) continue;
        pinMode(i, INPUT_PULLDOWN);
        digitalRead(i);
    }
    
    return false;
}
