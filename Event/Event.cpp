
#include "Event.h"
#include <iostream>


bool Compare::operator() (Event*& l, Event*& r) {
    return *l > *r;
}

bool operator<(const Event& l, const Event& r) {
    return l.get_priority() < r.get_priority();
}

bool operator>(const Event& l, const Event& r) {
    return r < l;
}

bool operator<=(const Event& l, const Event& r) {
    return !(l > r);
}

bool operator>=(const Event& l, const Event& r) {
    return !(r < l);
}

float Event::get_priority(void) const {
    return this->priority;
}
