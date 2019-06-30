#include "UniqueDebuff.h"

#include "Character.h"
#include "ClassStatistics.h"
#include "EnabledBuffs.h"
#include "RaidControl.h"
#include "Target.h"
#include "Utils/Check.h"

UniqueDebuff::UniqueDebuff(Character* pchar, QString name, QString icon, const int duration, const int base_charges) :
    Buff(pchar, name, icon, duration, base_charges)
{
    this->affected = Affected::Target;
}

void UniqueDebuff::enable_buff() {
    check(!enabled, QString("Tried to enable an already enabled UniqueDebuff '%1'").arg(name).toStdString());

    this->enabled = true;
    pchar->get_enabled_buffs()->add_buff(this);
}

void UniqueDebuff::disable_buff() {
    check(enabled, QString("Tried to disable an already disabled UniqueDebuff '%1'").arg(name).toStdString());

    pchar->get_enabled_buffs()->remove_buff(this);
    this->enabled = false;
}

void UniqueDebuff::prepare_set_of_combat_iterations() {
    initialize();

    if (this->is_hidden())
        return;

    this->statistics_buff = pchar->get_statistics()->get_buff_statistics(name, icon, Debuff::Yes);

    prepare_set_of_combat_iterations_spell_specific();
}

bool UniqueDebuff::apply_buff_to_target() {
    if (!raid_control->get_target()->add_debuff(this, debuff_priority))
        return false;

    buff_effect_when_applied();

    return true;
}

void UniqueDebuff::remove_buff_from_target() {
    pchar->get_target()->remove_debuff(this);
    buff_effect_when_removed();
}
