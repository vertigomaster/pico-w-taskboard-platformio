#include "buzzer_sfx.h"

#define BEEP_PIN DEVBOARD_BEEPER_PIN

namespace Beep {
    bool isSetup = false;

    bool Setup(){
#ifdef DEV_USING_LAFVIN_BREAKOUT_BOARD
        pinMode(BEEP_PIN, OUTPUT);
        isSetup = true;
        return true;
#else
        return false;
#endif
    }

    void ElementSetup()
    {
#ifdef DEV_USING_LAFVIN_BREAKOUT_BOARD
        if(!isSetup) return;
        digitalWrite(BEEP_PIN, HIGH);
        delay(20);
        digitalWrite(BEEP_PIN, LOW);
        delay(50);
        digitalWrite(BEEP_PIN, HIGH);
        delay(20);
        digitalWrite(BEEP_PIN, LOW);
        delay(100);
#endif
    }

    void Up3Notes(){
#ifdef DEV_USING_LAFVIN_BREAKOUT_BOARD
        if(!isSetup) return;
        analogWriteFreq(NOTE_D4);
        analogWrite(BEEP_PIN, 100);
        delay(150);
        analogWriteFreq(NOTE_F4);
        analogWrite(BEEP_PIN, 100);
        delay(150);
        analogWriteFreq(NOTE_A4);
        analogWrite(BEEP_PIN, 100);
        delay(150);
        analogWrite(BEEP_PIN, 0);
        delay(100);
#endif
    }

    void Yay()
    {
#ifdef DEV_USING_LAFVIN_BREAKOUT_BOARD
        if(!isSetup) return;
        analogWriteFreq(NOTE_A4);
        analogWrite(BEEP_PIN, 50);
        delay(250);
        analogWriteFreq(NOTE_G4);
        analogWrite(BEEP_PIN, 50);
        delay(250);
        analogWriteFreq(NOTE_C4);
        analogWrite(BEEP_PIN, 50);
        delay(250);
        analogWriteFreq(NOTE_A4);
        analogWrite(BEEP_PIN, 50);
        delay(250);
        analogWrite(BEEP_PIN, 0);
        delay(100);
#endif
    }

    void AllSystemsGo()
    {
#ifdef DEV_USING_LAFVIN_BREAKOUT_BOARD
        if(!isSetup) return;
        digitalWrite(BEEP_PIN, HIGH);
        delay(200);
        digitalWrite(BEEP_PIN, LOW);
        delay(100);
#endif
    }
}