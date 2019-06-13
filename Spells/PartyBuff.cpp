#include "PartyBuff.h"

#include "Character.h"
#include "ClassStatistics.h"
#include "RaidControl.h"
#include "Utils/Check.h"

PartyBuff::PartyBuff(Character* pchar, QString name, QString icon, const int duration, const int base_charges) :
    Buff(pchar, name, icon, duration, base_charges),
    party(pchar->get_party())
{
    this->affected = Affected::Party;
}

void PartyBuff::enable_buff() {
    check(!enabled, QString("Tried to enable an already enabled PartyBuff '%1'").arg(name).toStdString());

    this->enabled = true;
    raid_control->register_shared_party_buff(this, this->party);
}

void PartyBuff::disable_buff() {
    check(false, QString("Registered PartyBuff %1 cannot be disabled, it is destroyed upon RaidControl deletion.").arg(name).toStdString());
}

void PartyBuff::apply_buff_to(Character* any_pchar) {
    pchar = any_pchar;
    buff_effect_when_applied();
}

void PartyBuff::remove_buff_from(Character* any_pchar) {
    pchar = any_pchar;
    buff_effect_when_removed();
}

void PartyBuff::prepare_set_of_combat_iterations() {
    initialize();

    this->statistics_buff = raid_control->get_statistics()->get_buff_statistics(QString("%1 (party %2)").arg(name).arg(party + 1), icon, Debuff::No);

    prepare_set_of_combat_iterations_spell_specific();
}

bool PartyBuff::apply_buff_to_target() {
    raid_control->apply_party_buff(this, party);
    return true;
}

void PartyBuff::remove_buff_from_target() {
    raid_control->remove_party_buff(this, party);
}
