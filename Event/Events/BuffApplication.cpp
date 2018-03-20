
#include "BuffApplication.h"
#include "Buff.h"

#include <iostream>

BuffApplication::BuffApplication(const float timestamp, Buff* buff) {
    this->buff = buff;
    this->priority = timestamp;
    this->name = "BuffApplication";
}

void BuffApplication::act(void) {
    //std::cout << this->priority << ": BuffApplication\n";
    // Changes to character stats and the like is made within the context of Buff specialization.
    // This event is kept in case it needed in the future.
}
