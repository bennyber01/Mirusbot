#ifndef ACTION_QUEUE_H
#define ACTION_QUEUE_H

const int EVENT_QUEUE_SIZE = 10;

enum CommandType
{
    CT__NONE,
    CT__STOP,
    CT__GO_FORWARD,
    CT__GO_BACKWARD,
    CT__ROTATE_RIGHT,
    CT__ROTATE_LEFT,
    CT__ROTATE_IN_PLACE_RIGHT,
    CT__ROTATE_IN_PLACE_LEFT
};

struct CommandEntry
{
    CommandType command;

    union
    {
        int   param_int;
        float param_float;
    };

    CommandEntry() { Reset(); }

    void Reset() { command = CT__NONE; param_int = 0; }
};

class CommandQueue
{
public:
    CommandQueue();
    ~CommandQueue();

    void Reset();

    bool Push(CommandType c, int   param) { CommandEntry e; e.command = c; e.param_int   = param; return Push(e); }
    bool Push(CommandType c, float param) { CommandEntry e; e.command = c; e.param_float = param; return Push(e); }
    bool Push(CommandType c)              { CommandEntry e; e.command = c; e.param_int   = 0;     return Push(e); }
    bool Push(CommandEntry & entry);
    bool Pop(CommandEntry & entry);

private:
    CommandEntry commandQueue[EVENT_QUEUE_SIZE];
    int pushPlace;
    int popPlace;
};

//-------------------------------------------------------------------------------------

enum EventType
{
    ET__NONE,
    ET__GO_TO,
    ET__STOP
};

struct EventEntry
{
    EventType eventType;

    union
    {
        int   param_int0;
        float param_float0;
    };

    union
    {
        int   param_int1;
        float param_float1;
    };

    EventEntry() { Reset(); }

    void Reset() { eventType = ET__NONE; param_int0 = 0; param_int1 = 0; }
};

class EventQueue
{
public:
    EventQueue();
    ~EventQueue();

    void Reset();

    bool Push(EventType a, int   param0, int   param1) { EventEntry e; e.eventType = a; e.param_int0 = param0; e.param_int1 = param1; return Push(e); }
    bool Push(EventType a, float param0, float param1) { EventEntry e; e.eventType = a; e.param_int0 = param0; e.param_int1 = param1; return Push(e); }
    bool Push(EventType a)                             { EventEntry e; e.eventType = a; e.param_int0 = 0;      e.param_int1 = 0;      return Push(e); }
    bool Push(EventEntry & entry);
    bool Pop(EventEntry & entry);

private:
    EventEntry eventQueue[EVENT_QUEUE_SIZE];
    int pushPlace;
    int popPlace;
};

#endif // ACTIONQUEUE_H
