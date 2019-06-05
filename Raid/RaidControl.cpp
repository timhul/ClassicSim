#include "RaidControl.h"

#include "Buff.h"
#include "Utils/Check.h"

void RaidControl::apply_raid_buff(Buff* buff) {
    for (const auto & party : group_members) {
        for (const auto & pchar : party)
            buff->apply_buff_to(pchar);
    }
}

void RaidControl::apply_party_buff(Buff* buff, const int party) {
    check((party < group_members.size() && party >= 0), QString("Party %1 out of bounds").arg(party).toStdString());

    for (const auto & pchar : group_members[party])
        buff->apply_buff_to(pchar);
}

void RaidControl::remove_raid_buff(Buff* buff) {
    for (const auto & party : group_members) {
        for (const auto & pchar : party)
            buff->remove_buff_from(pchar);
    }
}

void RaidControl::remove_party_buff(Buff* buff, const int party) {
    check((party < group_members.size() && party >= 0), QString("Party %1 out of bounds").arg(party).toStdString());

    for (const auto & pchar : group_members[party])
        buff->remove_buff_from(pchar);
}

int RaidControl::next_instance_id() {
    return ++instance_id;
}
