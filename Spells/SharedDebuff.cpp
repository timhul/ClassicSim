#include "SharedDebuff.h"

#include "Character.h"
#include "ClassStatistics.h"
#include "Utils/Check.h"
#include "RaidControl.h"

SharedDebuff::SharedDebuff(RaidControl* raid_control, QString name, QString icon, const int duration, const int base_charges) :
    Buff(raid_control, name, icon, duration, base_charges)
{
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

void SharedDebuff::apply_buff_to(Character* any_pchar) {
    pchar = any_pchar;
    buff_effect_when_applied();
}

void SharedDebuff::remove_buff_from(Character* any_pchar) {
    pchar = any_pchar;
    buff_effect_when_removed();
}

void SharedDebuff::prepare_set_of_combat_iterations() {
    initialize();

    if (this->is_hidden())
        return;

    this->statistics_buff = raid_control->get_statistics()->get_buff_statistics(name, icon, Debuff::Yes);

    prepare_set_of_combat_iterations_spell_specific();
}

void SharedDebuff::apply_buff_to_target() {
    raid_control->apply_raid_buff(this);
}

void SharedDebuff::remove_buff_from_target() {
    raid_control->remove_raid_buff(this);
}
