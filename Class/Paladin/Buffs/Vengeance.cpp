#include "Vengeance.h"

#include "CharacterSpells.h"
#include "CharacterStats.h"
#include "Paladin.h"

Vengeance::Vengeance(Paladin* pchar):
    Buff(pchar, "Vengeance", "Assets/ability/Ability_racial_avatar.png", 8, 0),
    TalentRequirer(QVector<TalentRequirerInfo*>{new TalentRequirerInfo("Vengeance", 5, DisabledAtZero::Yes)}),
    paladin(dynamic_cast<Paladin*>(pchar))
{
    enabled = false;
    dmg_bonuses = {0, 3, 6, 9, 12, 15};
}

void Vengeance::buff_effect_when_applied() {
    pchar->get_stats()->increase_total_phys_dmg_mod(dmg_bonus);
    pchar->get_stats()->increase_spell_dmg_mod(dmg_bonus, MagicSchool::Holy);
}

void Vengeance::buff_effect_when_removed() {
    pchar->get_stats()->decrease_total_phys_dmg_mod(dmg_bonus);
    pchar->get_stats()->decrease_spell_dmg_mod(dmg_bonus, MagicSchool::Holy);
}

void Vengeance::increase_talent_rank_effect(const QString&, const int curr) {
    dmg_bonus = dmg_bonuses[curr];
}

void Vengeance::decrease_talent_rank_effect(const QString&, const int curr) {
    dmg_bonus = dmg_bonuses[curr];
}
