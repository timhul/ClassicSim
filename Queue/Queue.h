#pragma once

#include <queue>

#include "Event.h"

class Queue {
public:
    ~Queue();

    Event* get_next();
    Event* peek();
    void push(Event*);
    bool empty();
    void pop();
    void clear();

private:
    std::priority_queue<Event*, std::vector<Event*>, Compare> queue;
};
