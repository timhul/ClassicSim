#include "PeriodicRefreshBuff.h"

#include "Buff.h"

PeriodicRefreshBuff::PeriodicRefreshBuff(Buff* buff, const double timestamp):
    Event(EventType::PeriodicRefreshBuff, timestamp),
    buff(buff)
{}

void PeriodicRefreshBuff::act() {
    buff->refresh_buff();
}
