#ifndef QUEUE_H
#define QUEUE_H

#include <queue>
#include "Event.h"

class Queue {
public:
    Event* get_next(void);
    void push(Event*);
    bool empty(void);
    void pop(void);

    std::priority_queue<Event*, std::vector<Event*>, Compare> queue;

protected:

private:
     // std::priority_queue<Event*, std::vector<Event*>, Compare> queue;


};

#endif // QUEUE_H
