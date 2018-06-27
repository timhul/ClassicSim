
#include "Queue.h"

Queue::~Queue() {
    this->clear();
}

Event* Queue::get_next(void) {
    Event* top = this->queue.top();
    this->queue.pop();
    return top;
}

void Queue::push(Event* event) {
    this->queue.push(event);
}

bool Queue::empty(void) {
    return this->queue.empty();
}

void Queue::clear(void) {
    while (!this->queue.empty()) {
        Event* top = get_next();
        delete top;
    }
}
