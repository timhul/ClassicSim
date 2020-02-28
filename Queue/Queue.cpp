#include "Queue.h"

Queue::~Queue() {
    this->clear();
}

Event* Queue::get_next() {
    Event* top = this->queue.top();
    this->queue.pop();
    return top;
}

Event* Queue::peek() {
    return this->queue.top();
}

void Queue::push(Event* event) {
    this->queue.push(event);
}

bool Queue::empty() {
    return this->queue.empty();
}

void Queue::clear() {
    while (!this->queue.empty()) {
        Event* top = get_next();
        delete top;
    }
}
