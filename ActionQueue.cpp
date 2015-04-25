#include "ActionQueue.h"

ActionQueue::ActionQueue()
{
    Reset();
}

ActionQueue::~ActionQueue()
{
    Reset();
}

void ActionQueue::Reset()
{
    pushPlace = 0;
    popPlace = 0;
}

bool ActionQueue::Push(ActionEntry & entry)
{
    eventQueue[pushPlace] = entry;
    pushPlace++;
    if (pushPlace >= EVENT_QUEUE_SIZE)
        pushPlace = 0;
    return true;
}

bool ActionQueue::Pop(ActionEntry & entry)
{
    entry.Reset();

    if (eventQueue[popPlace].actionType == AT__NONE)
        return false;

    entry = eventQueue[popPlace];
    eventQueue[popPlace].actionType = AT__NONE;
    popPlace++;
    if (popPlace >= EVENT_QUEUE_SIZE)
        popPlace = 0;
    return true;
}
