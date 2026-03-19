#include "GPIOTaskRow.h"

//debug only
// #define BEEPER_PIN 13u

void TactileTaskBoard::GPIOTaskRow::Setup()
{
    // ITaskButton& butt = GetButton();
    // ITaskLED& led = GetLED();

    // butt.AttachInterrupt(led.Toggle); //what do we pass this as?

    pinMode(gpioButtonPin, INPUT_PULLDOWN);
    pinMode(gpioLedPin, OUTPUT);
    _isInputEnabled = true;
 
    AttachInterrupt();
}

// abstracted since we'll migrate from direct GPIO pin reading to checking from an I2C expander
bool TactileTaskBoard::GPIOTaskRow::IsPressed_Raw()
{
    return _pressedState_interrupt;
}

bool TactileTaskBoard::GPIOTaskRow::IsPressed_Clean()
{
    return _pressedState_clean;
}

// are there pending changes that dirtied the state since it was last checked?
bool TactileTaskBoard::GPIOTaskRow::IsDirty()
{
    // if internal pressed no longer matches
    return _isDirtyFlag;// || _pressedState_interrupt != _pressedState_clean;
}

void TactileTaskBoard::GPIOTaskRow::TakeCleanStateSnapshot()
{
    //TODO: Later on we could have it return a snapshot object
    //Is a bit overkill for the hobby project this was originally written for, 
    //but would make the library easier to use.

    // only the ISR writes to the _interrupt_pressed state
    _pressedState_clean = _pressedState_interrupt;
    _isDirtyFlag = false;
}

void TactileTaskBoard::GPIOTaskRow::AttachInterrupt()
{
    //apparently can only have interrupt attached to a particular pin, so we'll need to monitor all changes and just try to query

    // interrupts are hardware and live in native c, not c++, so no Object-oriented semantics
    // attaches the interrupt to a static function that takes in a pointer to our object as a parameter
    // said static func then uses that pointer to invoke our instance's callback function
    //(this is the kind of stuff macros are for)
    attachInterrupt(
        digitalPinToInterrupt(gpioButtonPin),
        OnButtonChangeWrapper,
        CHANGE, // what event to attach the interrupt to
        this);  // param to manually pass into the native func
}

void TactileTaskBoard::GPIOTaskRow::InterruptCallback_OnButtonChange()
{
    PinStatus currentState = digitalRead(gpioButtonPin);
    if(currentState == HIGH){
        InterruptCallback_OnButtonPress();
    } else {
        InterruptCallback_OnButtonRelease();
    } 
}

void TactileTaskBoard::GPIOTaskRow::InterruptCallback_OnButtonPress()
{
    // digitalWrite(BEEPER_PIN, HIGH);

    if(!_isInputEnabled) return;
    
    _pressedState_interrupt = true;
    _isDirtyFlag = true;
    Serial.println("fooble - interrupt; button press");

    MarkTaskComplete(!_taskCompleted);

    // don't want interrupts to take too long since they immediately "interrupt" whatever the
    // CPU was doing - at any time, be that WiFi shenanigans or anything time sensitive
    // luckily the hardware on these is pretty small scale, but still.
}

void TactileTaskBoard::GPIOTaskRow::InterruptCallback_OnButtonRelease()
{
    // digitalWrite(BEEPER_PIN, HIGH);
    // delay(100);
    // digitalWrite(BEEPER_PIN, LOW);
    // delay(100);

    if(!_isInputEnabled) return;

    _pressedState_interrupt = false;
    Serial.println("fooble - interrupt; button release");
    // SetLEDState(false);
    // don't want interrupts to take too long since they immediately "interrupt" whatever the
    // CPU was doing - at any time, be that WiFi shenanigans or anything time sensitive
    // luckily the hardware on these is pretty small scale, but still.
}

void TactileTaskBoard::GPIOTaskRow::SetLEDState(bool shouldTurnOn)
{
    if(shouldTurnOn)
        digitalWrite(gpioLedPin, HIGH);
    else
        digitalWrite(gpioLedPin, LOW);
}

bool TactileTaskBoard::GPIOTaskRow::IsInputEnabled()
{
    return _isInputEnabled;
}

//global switch for deciding whether the interrupt should do anything
void TactileTaskBoard::GPIOTaskRow::EnableInput(bool shouldEnableInput)
{
    _isInputEnabled = shouldEnableInput;
}
