#include "RaidControl.h"

#include "Buff.h"
#include "Character.h"
#include "ClassStatistics.h"
#include "Engine.h"
#include "PartyBuff.h"
#include "SharedDebuff.h"
#include "Target.h"
#include "Utils/Check.h"

RaidControl::RaidControl(SimSettings* sim_settings) :
    raid_statistics(new ClassStatistics(sim_settings, true)),
    settings(sim_settings),
    engine(new Engine()),
    target(new Target(63))
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
    delete target;
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

void RaidControl::apply_party_buff(PartyBuff* buff, const int party) {
    check((party < group_members.size() && party >= 0), QString("Apply party buff party %1 out of bounds").arg(party).toStdString());

    for (const auto & pchar : group_members[party]) {
        if (pchar != nullptr)
            buff->apply_buff_to(pchar);
    }
}

void RaidControl::remove_party_buff(PartyBuff* buff, const int party) {
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
    check(buff->is_enabled(), QString("Tried to register PartyBuff %1 but it is not enabled").arg(buff->get_name()).toStdString());

    if (buff->get_instance_id() == InstanceID::INACTIVE)
        buff->set_instance_id(next_instance_id());

    shared_party_buffs[party][buff->get_name()] = buff;
}

Buff* RaidControl::get_shared_party_buff(const QString& buff_name, const int party) const {
    if (!shared_party_buffs[party].contains(buff_name))
        return nullptr;

    return shared_party_buffs[party][buff_name];
}

void RaidControl::register_shared_raid_buff(SharedDebuff* buff) {
    check(!shared_raid_buffs.contains(buff->get_name()), QString("Tried to register already registered raid buff %1").arg(buff->get_name()).toStdString());
    check(buff->is_enabled(), QString("Tried to register raid buff %1 but it is not enabled").arg(buff->get_name()).toStdString());

    if (buff->get_instance_id() == InstanceID::INACTIVE)
        buff->set_instance_id(next_instance_id());

    shared_raid_buffs[buff->get_name()] = buff;
}

Buff* RaidControl::get_shared_raid_buff(const QString& buff_name) const {
    if (!shared_raid_buffs.contains(buff_name))
        return nullptr;

    return shared_raid_buffs[buff_name];
}

void RaidControl::reset() {
    for (const auto & buff : shared_raid_buffs)
        buff->reset();

    for (const auto & party_buffs : shared_party_buffs)
        for (const auto & buff : party_buffs)
            buff->reset();
}

void RaidControl::prepare_set_of_combat_iterations() {
    for (const auto & buff : shared_raid_buffs)
        buff->prepare_set_of_combat_iterations();

    for (const auto & party_buffs : shared_party_buffs)
        for (const auto & buff : party_buffs)
            buff->prepare_set_of_combat_iterations();
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

Target* RaidControl::get_target() const {
    return this->target;
}

SimSettings* RaidControl::get_sim_settings() const {
    return this->settings;
}

QVector<QVector<Character*>> RaidControl::get_raid_members() const {
    return group_members;
}
