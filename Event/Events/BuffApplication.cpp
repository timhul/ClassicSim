
#include "BuffApplication.h"
#include "Buff.h"

BuffApplication::BuffApplication(const float timestamp, Buff* buff) {
    this->buff = buff;
    this->priority = timestamp;
    this->name = "BuffApplication";
}

void BuffApplication::act(void) {
    // Changes to character stats and the like is made within the context of Buff specialization.
    // This event is kept in case it needed in the future.
}
