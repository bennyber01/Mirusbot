#ifndef ACTION_QUEUE_H
#define ACTION_QUEUE_H

const int EVENT_QUEUE_SIZE = 10;

enum ActionType
{
    AT__NONE,
    AT__STOP,
    AT__GO_FORWARD,
    AT__GO_BACKWARD,
    AT__ROTATE_RIGHT,
    AT__ROTATE_LEFT,
    AT__ROTATE_IN_PLACE_RIGHT,
    AT__ROTATE_IN_PLACE_LEFT
};

struct ActionEntry
{
    ActionType actionType;

    union
    {
        int   param_int;
        float param_float;
    };

    ActionEntry()                          { actionType = AT__NONE; param_int   = 0;     }
    ActionEntry(ActionType a)              { actionType = a;        param_int   = 0;     }
    ActionEntry(ActionType a, int   param) { actionType = a;        param_int   = param; }
    ActionEntry(ActionType a, float param) { actionType = a;        param_float = param; }

    void Reset()                           { actionType = AT__NONE; param_int   = 0;     }
};

class ActionQueue
{
public:
    ActionQueue();
    ~ActionQueue();

    void Reset();

    bool Push(ActionType a, int   param) { ActionEntry e(a, param); return Push(e); }
    bool Push(ActionType a, float param) { ActionEntry e(a, param); return Push(e); }
    bool Push(ActionEntry & entry);
    bool Pop(ActionEntry & entry);

private:
    ActionEntry eventQueue[EVENT_QUEUE_SIZE];
    int pushPlace;
    int popPlace;
};

#endif // ACTIONQUEUE_H
