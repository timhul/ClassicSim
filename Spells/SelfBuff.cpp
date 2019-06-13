#include "SelfBuff.h"

#include "Character.h"
#include "ClassStatistics.h"
#include "EnabledBuffs.h"
#include "Utils/Check.h"

SelfBuff::SelfBuff(Character* pchar, QString name, QString icon, const int duration, const int base_charges):
    Buff(pchar, name, icon, duration, base_charges)
{}

void SelfBuff::enable_buff() {
    check(!enabled, QString("Tried to enable an already enabled SelfBuff '%1'").arg(name).toStdString());

    this->enabled = true;
    pchar->get_enabled_buffs()->add_buff(this);
}

void SelfBuff::disable_buff() {
    check(enabled, QString("Tried to disable an already disabled SelfBuff '%1'").arg(name).toStdString());

    pchar->get_enabled_buffs()->remove_buff(this);
    this->enabled = false;
}

void SelfBuff::prepare_set_of_combat_iterations() {
    initialize();

    if (this->is_hidden())
        return;

    this->statistics_buff = pchar->get_statistics()->get_buff_statistics(name, icon, Debuff::No);

    prepare_set_of_combat_iterations_spell_specific();
}

bool SelfBuff::apply_buff_to_target() {
    buff_effect_when_applied();
    return true;
}

void SelfBuff::remove_buff_from_target() {
    buff_effect_when_removed();
}
