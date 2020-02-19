#include "BuffRemoval.h"

#include "Buff.h"

BuffRemoval::BuffRemoval(Buff* buff, const double timestamp, const int iteration) :
    Event(EventType::BuffRemoval, timestamp), buff(buff), iteration(iteration) {}

void BuffRemoval::act() {
    buff->remove_buff(iteration);
}
