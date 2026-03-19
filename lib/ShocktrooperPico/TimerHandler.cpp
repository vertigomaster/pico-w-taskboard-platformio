#include "TimerHandler.h"

void ShocktrooperPico::TimerHandler::InterruptCaptureTime()
{
    old_time = new_time;
    new_time = time_us_64();
    counter++;
}

long ShocktrooperPico::TimerHandler::GetTimeDifference()
{
    return new_time - old_time;
}
