#include "Event.h"

bool Compare::operator() (Event*& l, Event*& r) {
    return *l > *r;
}

bool operator<(const Event& l, const Event& r) {
    return l.priority < r.priority;
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

Event::Event(Events event_enum_val, const double priority, const QString& name):
    event(event_enum_val),
    priority(priority),
    name(name)
{}
