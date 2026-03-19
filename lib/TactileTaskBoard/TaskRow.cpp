#include "TaskRow.h"

void TactileTaskBoard::GPIOTaskRow::Setup()
{
    // ITaskButton& butt = GetButton();
    // ITaskLED& led = GetLED();

    // butt.AttachInterrupt(led.Toggle); //what do we pass this as?

    pinMode(_gpioButtonPin, INPUT_PULLUP);
    pinMode(_gpioLedPin, OUTPUT);
    AttachInterrupt();
}

void TactileTaskBoard::GPIOTaskRow::AttachInterrupt()
{
    //interrupts are hardware and live in native c, not c++, so no Object-oriented semantics
    //attaches the interrupt to a static function that takes in a pointer to our object as a parameter
    //said static func then uses that pointer to invoke our instance's callback function
    //(this is the kind of stuff macros are for)
    attachInterrupt(
        digitalPinToInterrupt(_gpioButtonPin), 
        TactileTaskBoard::OnButtonPressWrapper_GPIO, 
        FALLING, //what event to attach the interrupt to
        this); //param to manually pass into the native func

    attachInterrupt(
        digitalPinToInterrupt(_gpioButtonPin), 
        TactileTaskBoard::OnButtonReleaseWrapper_GPIO, 
        RISING, //what event to attach the interrupt to
        this); //param to manually pass into the native func
}

void TactileTaskBoard::OnButtonPressWrapper_GPIO(TactileTaskBoard::GPIOTaskRow* row){ row->InterruptCallback_OnButtonPress(); }
void TactileTaskBoard::GPIOTaskRow::InterruptCallback_OnButtonPress()
{
    _pressed = true;
    Serial.println("fooble - interrupt; button press");
    TurnOnLED();

    //don't want interrupts to take too long since they immediately "interrupt" whatever the 
    //CPU was doing - at any time, be that WiFi shenanigans or anything time sensitive
    //luckily the hardware on these is pretty small scale, but still.
}

void TactileTaskBoard::OnButtonReleaseWrapper_GPIO(TactileTaskBoard::GPIOTaskRow* row){ row->InterruptCallback_OnButtonRelease(); }
void TactileTaskBoard::GPIOTaskRow::InterruptCallback_OnButtonRelease()
{
    _pressed = false;
    Serial.println("fooble - interrupt; button release");
    TurnOffLED();
    //don't want interrupts to take too long since they immediately "interrupt" whatever the 
    //CPU was doing - at any time, be that WiFi shenanigans or anything time sensitive
    //luckily the hardware on these is pretty small scale, but still.
}

void TactileTaskBoard::GPIOTaskRow::TurnOnLED()
{
    digitalWrite(_gpioLedPin, HIGH);
}
void TactileTaskBoard::GPIOTaskRow::TurnOffLED()
{
    digitalWrite(_gpioLedPin, LOW);
}