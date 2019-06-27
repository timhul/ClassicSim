#include "PeriodicRefreshBuff.h"

#include "Buff.h"

PeriodicRefreshBuff::PeriodicRefreshBuff(Buff* buff, const double timestamp):
    Event(Events::PeriodicRefreshBuff, timestamp, "PeriodicRefreshBuff"),
    buff(buff)
{}

void PeriodicRefreshBuff::act() {
    buff->refresh_buff();
}
