#include "CoreImpl_GPIO.h"

void OnButtonPressWrapper(TactileTaskBoard::GPIOTaskButton* btn){
    //todo: trigger some lambda stored on the object instead, as the button doesn't have this context
    btn->OnButtonPress();
}

void TactileTaskBoard::GPIOTaskButton::AttachInterrupt()
{
    attachInterrupt(digitalPinToInterrupt(_gpioPin), OnButtonPressWrapper, FALLING, this);
}

void TactileTaskBoard::GPIOTaskButton::OnButtonPress(){
    //toggle the LED
}