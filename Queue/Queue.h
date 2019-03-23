#ifndef QUEUE_H
#define QUEUE_H

#include <queue>
#include "Event.h"

class Queue {
public:
    ~Queue();

    Event* get_next();
    void push(Event*);
    bool empty();
    void pop();
    void clear();

protected:

private:
     std::priority_queue<Event*, std::vector<Event*>, Compare> queue;
};

#endif // QUEUE_H
