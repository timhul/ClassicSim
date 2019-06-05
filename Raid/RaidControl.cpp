#include "RaidControl.h"

#include "Buff.h"
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

void RaidControl::assign_character_to_group(Character* pchar) {
    group_members[0].append(pchar);
}

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
