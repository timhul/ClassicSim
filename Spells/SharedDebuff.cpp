#include "SharedDebuff.h"

#include "Character.h"
#include "ClassStatistics.h"
#include "RaidControl.h"
#include "Target.h"
#include "Utils/Check.h"

SharedDebuff::SharedDebuff(Character* pchar, QString name, QString icon, const Priority priority, const int duration, const int base_charges) :
    Buff(pchar, name, icon, duration, base_charges)
{
    check((priority != Priority::Invalid), QString("Cannot create UniqueDebuff %1 with invalid priority").arg(name).toStdString());
    this->debuff_priority = priority;

    this->affected = Affected::Target;
}

void SharedDebuff::enable_buff() {
    check(!enabled, QString("Tried to enable an already enabled SharedDebuff '%1'").arg(name).toStdString());

    this->enabled = true;
    raid_control->register_shared_raid_buff(this);
}

void SharedDebuff::disable_buff() {
    check(false, QString("Registered SharedDebuff %1 cannot be disabled, it is destroyed upon RaidControl deletion.").arg(name).toStdString());
}

void SharedDebuff::prepare_set_of_combat_iterations() {
    initialize();

    if (this->is_hidden())
        return;

    this->statistics_buff = raid_control->get_statistics()->get_buff_statistics(name, icon, Debuff::Yes);

    prepare_set_of_combat_iterations_spell_specific();
}

bool SharedDebuff::apply_buff_to_target() {
    if (!raid_control->get_target()->add_debuff(this, debuff_priority))
        return false;

    buff_effect_when_applied();

    return true;
}

void SharedDebuff::remove_buff_from_target() {
    pchar->get_target()->remove_debuff(this);
    buff_effect_when_removed();
}
