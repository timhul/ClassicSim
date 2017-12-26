
#include "Queue.h"

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
