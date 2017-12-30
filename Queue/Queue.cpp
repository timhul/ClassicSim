
#include "Queue.h"

Event* Queue::get_next(void) {
    Event* top = this->action_queue.top();
    this->action_queue.pop();
    return top;
}

void Queue::push(Event* event) {
    this->action_queue.push(event);
}

bool Queue::empty(void) {
    return this->action_queue.empty();
}

void Queue::clear(void) {
    while (!this->action_queue.empty()) {
        Event* top = get_next();
        delete top;
    }
}
