#pragma once
#include "pico/stdlib.h"
#include "pico/time.h"
#include <cstdio>

namespace ShocktrooperPico {
    class TimerHandler {
        private:
        int counter;
        long old_time;
        long new_time;

        public:
        TimerHandler() : counter(0), old_time(0), new_time(0) {}

        //Interrupt method
        void InterruptCaptureTime();
        long GetTimeDifference();
    };
}