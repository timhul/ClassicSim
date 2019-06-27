#include "BuffRemoval.h"

#include "Buff.h"

BuffRemoval::BuffRemoval(Buff* buff, const double timestamp, const int iteration):
    Event(Events::BuffRemoval, timestamp, "BuffRemoval"),
    buff(buff),
    iteration(iteration)
{}

void BuffRemoval::act() {
    buff->remove_buff(iteration);
}
