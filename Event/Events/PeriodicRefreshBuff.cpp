
#include "PeriodicRefreshBuff.h"
#include "Buff.h"
#include "Engine.h"
#include "Character.h"

PeriodicRefreshBuff::PeriodicRefreshBuff(Character* pchar, Buff* buff, const double priority) {
    this->pchar = pchar;
    this->buff = buff;
    this->priority = priority;
    this->name = "PeriodicRefreshBuff";
}

void PeriodicRefreshBuff::act() {
    buff->refresh_buff();
}
