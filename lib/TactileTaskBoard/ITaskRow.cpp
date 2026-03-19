#include <ITaskRow.h>
void TactileTaskBoard::ITaskRow::MarkTaskComplete(bool doComplete) 
{ 
    _taskCompleted = doComplete; 
    SetLEDState(doComplete);
}