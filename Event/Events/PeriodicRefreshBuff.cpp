#include "PeriodicRefreshBuff.h"

#include "Buff.h"
#include "Character.h"
#include "Engine.h"

PeriodicRefreshBuff::PeriodicRefreshBuff(Character* pchar, Buff* buff, const double timestamp):
    Event(Events::PeriodicRefreshBuff)
{
    this->pchar = pchar;
    this->buff = buff;
    this->priority = timestamp;
    this->name = "PeriodicRefreshBuff";
}

void PeriodicRefreshBuff::act() {
    buff->refresh_buff();
}
