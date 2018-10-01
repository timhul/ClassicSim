
#include "Event.h"

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

double Event::get_priority() const {
    return this->priority;
}

QString Event::get_name() const {
    return this->name;
}
