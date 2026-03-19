#pragma once
#include <Arduino.h>
#include <functional>

namespace PicoDiagnostics {
    uint32_t RunTestOnAllGPIOs(std::function<bool(pin_size_t)> pinTestImpl);

    uint32_t RunStandardTestsOnAllGPIOs();

    bool TestGPIOPin_VoltageShorts(pin_size_t pinNumber);
    bool TestGPIOPin_GroundShorts(pin_size_t pinNumber);
    bool TestGPIOPin_Bridges(pin_size_t pinNumber);
    void SetAllGPIOsOutHigh();
}