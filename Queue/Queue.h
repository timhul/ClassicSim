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
    void clear(void);

protected:

private:
     std::priority_queue<Event*, std::vector<Event*>, Compare> action_queue;
     std::priority_queue<Event*, std::vector<Event*>, Compare> mh_queue;
     std::priority_queue<Event*, std::vector<Event*>, Compare> oh_queue;

};

#endif // QUEUE_H
