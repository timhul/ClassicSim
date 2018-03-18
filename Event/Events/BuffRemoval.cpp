
#include "BuffRemoval.h"
#include "Buff.h"

#include <iostream>

BuffRemoval::BuffRemoval(Buff* buff, const float timestamp) {
    this->buff = buff;
    this->priority = timestamp;
}

void BuffRemoval::act(void) {
    std::cout << this->priority << ": BuffRemoval\n";
    buff->remove_buff();
}
