#include "ElementalDevastation.h"

#include "Character.h"
#include "CharacterStats.h"

ElementalDevastation::ElementalDevastation(Character* pchar):
    SelfBuff(pchar, "Elemental Devastation", "Assets/spell/Spell_fire_elementaldevastation.png", 10, 0),
    TalentRequirer(QVector<TalentRequirerInfo*>{new TalentRequirerInfo("Elemental Devastation", 3, DisabledAtZero::Yes)})
{}

void ElementalDevastation::buff_effect_when_applied() {
    pchar->get_stats()->increase_melee_crit(crit_bonus);
}

void ElementalDevastation::buff_effect_when_removed() {
    pchar->get_stats()->decrease_melee_crit(crit_bonus);
}

void ElementalDevastation::increase_talent_rank_effect(const QString&, const int curr) {
    crit_bonus = crit_bonus_ranks[curr];
}

void ElementalDevastation::decrease_talent_rank_effect(const QString&, const int curr) {
    crit_bonus = crit_bonus_ranks[curr];
}
