#include "RaidControl.h"

#include "Buff.h"
#include "Character.h"
#include "ClassStatistics.h"
#include "Engine.h"
#include "Utils/Check.h"

RaidControl::RaidControl(SimSettings* sim_settings) :
    raid_statistics(new ClassStatistics(sim_settings, true)),
    settings(sim_settings),
    engine(new Engine())
{
    for (int i = 0; i < 8; ++i) {
        group_members.append(QVector<Character*>());
        for (int j = 0; j < 5; ++j)
            group_members[i].append(nullptr);

        shared_party_buffs.append(QMap<QString, Buff*>());
    }
}

RaidControl::~RaidControl() {
    for (const auto & party : shared_party_buffs) {
        for (const auto & buff : party)
            delete buff;
    }

    for (const auto & buff : shared_raid_buffs)
        delete buff;

    delete raid_statistics;
    delete engine;
}

QPair<int, int> RaidControl::auto_assign_character_to_group(Character* pchar) {
    for (int i = 0; i < group_members.size(); ++i) {
        for (int j = 0; j < group_members[i].size(); ++j) {
            if (group_members[i][j] == nullptr) {
                group_members[i][j] = pchar;
                return QPair<int, int>{i, j};
            }
        }
    }

    check(false, "Failed to auto assign character to raid group");
}

void RaidControl::assign_character_to_place(Character* pchar, const int party, const int member) {
    check((party < group_members.size() && party >= 0), QString("Assign character to place party %1 out of bounds").arg(party).toStdString());

    delete group_members[party][member];
    group_members[party][member] = pchar;
}

void RaidControl::apply_raid_buff(Buff* buff) {
    for (const auto & party : group_members) {
        for (const auto & pchar : party) {
            if (pchar != nullptr)
                buff->apply_buff_to(pchar);
        }
    }
}

void RaidControl::apply_party_buff(Buff* buff, const int party) {
    check((party < group_members.size() && party >= 0), QString("Apply party buff party %1 out of bounds").arg(party).toStdString());

    for (const auto & pchar : group_members[party]) {
        if (pchar != nullptr)
            buff->apply_buff_to(pchar);
    }
}

void RaidControl::remove_raid_buff(Buff* buff) {
    for (const auto & party : group_members) {
        for (const auto & pchar : party) {
            if (pchar != nullptr)
                buff->remove_buff_from(pchar);
        }
    }
}

void RaidControl::clear_all_buffs() {
    for (int i = 0; i < group_members.size(); ++i) {
        for (const auto & buff : shared_party_buffs[i])
            buff->cancel_buff();

        shared_party_buffs[i].clear();
    }

    for (const auto & buff : shared_raid_buffs)
        buff->cancel_buff();

    shared_raid_buffs.clear();
}

void RaidControl::remove_party_buff(Buff* buff, const int party) {
    check((party < group_members.size() && party >= 0), QString("Party %1 out of bounds").arg(party).toStdString());

    for (const auto & pchar : group_members[party]) {
        if (pchar != nullptr)
            buff->remove_buff_from(pchar);
    }
}

int RaidControl::next_instance_id() {
    return ++instance_id;
}

void RaidControl::register_shared_party_buff(Buff* buff, const int party) {
    check(!shared_party_buffs[party].contains(buff->get_name()), QString("Tried to register already registered party buff %1").arg(buff->get_name()).toStdString());
    check((buff->get_affected() == Affected::Party), QString("Tried to register non-party buff %1 as a party buff").arg(buff->get_name()).toStdString());

    shared_party_buffs[party][buff->get_name()] = buff;
}

Buff* RaidControl::get_shared_party_buff(const QString& buff_name, const int party) const {
    if (!shared_party_buffs[party].contains(buff_name))
        return nullptr;

    return shared_party_buffs[party][buff_name];
}

void RaidControl::register_shared_raid_buff(Buff *buff) {
    check(!shared_raid_buffs.contains(buff->get_name()), QString("Tried to register already registered raid buff %1").arg(buff->get_name()).toStdString());
    check((buff->get_affected() == Affected::Raid), QString("Tried to register non-raid buff %1 as a raid buff").arg(buff->get_name()).toStdString());

    shared_raid_buffs[buff->get_name()] = buff;
}

Buff* RaidControl::get_shared_raid_buff(const QString& buff_name) const {
    if (shared_raid_buffs.contains(buff_name))
        return nullptr;

    return shared_raid_buffs[buff_name];
}

ClassStatistics* RaidControl::get_statistics() const {
    return this->raid_statistics;
}

ClassStatistics* RaidControl::relinquish_ownership_of_statistics() {
    ClassStatistics* tmp = this->raid_statistics;
    this->raid_statistics = new ClassStatistics(settings);
    return tmp;
}

Engine* RaidControl::get_engine() const {
    return this->engine;
}

QVector<QVector<Character*>> RaidControl::get_raid_members() const {
    return group_members;
}
