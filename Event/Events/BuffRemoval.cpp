
#include "BuffRemoval.h"
#include "Buff.h"

BuffRemoval::BuffRemoval(Buff* buff, const double timestamp, const int iteration) {
    this->buff = buff;
    this->priority = timestamp;
    this->iteration = iteration;
    this->name = "BuffRemoval";
}

void BuffRemoval::act() {
    buff->remove_buff(iteration);
}
