#include "ActionQueue.h"

CommandQueue::CommandQueue()
{
    Reset();
}

CommandQueue::~CommandQueue()
{
    Reset();
}

void CommandQueue::Reset()
{
    pushPlace = 0;
    popPlace = 0;
}

bool CommandQueue::Push(CommandEntry & entry)
{
    commandQueue[pushPlace] = entry;
    pushPlace++;
    if (pushPlace >= EVENT_QUEUE_SIZE)
        pushPlace = 0;
    return true;
}

bool CommandQueue::Pop(CommandEntry & entry)
{
    entry.Reset();

    if (commandQueue[popPlace].command == CT__NONE)
        return false;

    entry = commandQueue[popPlace];
    commandQueue[popPlace].command = CT__NONE;
    popPlace++;
    if (popPlace >= EVENT_QUEUE_SIZE)
        popPlace = 0;
    return true;
}

//-------------------------------------------------------------------------------------

EventQueue::EventQueue()
{
    Reset();
}

EventQueue::~EventQueue()
{
    Reset();
}

void EventQueue::Reset()
{
    pushPlace = 0;
    popPlace = 0;
}

bool EventQueue::Push(EventEntry & entry)
{
    eventQueue[pushPlace] = entry;
    pushPlace++;
    if (pushPlace >= EVENT_QUEUE_SIZE)
        pushPlace = 0;
    return true;
}

bool EventQueue::Pop(EventEntry & entry)
{
    entry.Reset();

    if (eventQueue[popPlace].eventType == ET__NONE)
        return false;

    entry = eventQueue[popPlace];
    eventQueue[popPlace].eventType = ET__NONE;
    popPlace++;
    if (popPlace >= EVENT_QUEUE_SIZE)
        popPlace = 0;
    return true;
}
