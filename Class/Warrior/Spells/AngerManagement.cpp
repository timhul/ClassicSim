#include "AngerManagement.h"

#include "Resource.h"
#include "Utils/Check.h"
#include "Warrior.h"
#include "WarriorSpells.h"

AngerManagement::AngerManagement(Warrior* warrior, WarriorSpells* warrior_spells) :
    PeriodicResourceGainSpell("Anger Management", "Assets/spell/Spell_holy_blessingofstamina.png", warrior, RestrictedByGcd::No, 3.0,
                              std::numeric_limits<int>::max(), {{ResourceType::Rage, 1}}),
    TalentRequirer(QVector<TalentRequirerInfo*>{new TalentRequirerInfo("Anger Management", 1, DisabledAtZero::Yes)}),
    warrior(warrior),
    warrior_spells(warrior_spells)
{
    this->enabled = false;
}

void AngerManagement::perform_start_of_combat() {
    perform();
}

void AngerManagement::increase_talent_rank_effect(const QString&, const int) {
    warrior_spells->add_start_of_combat_spell(this);
}

void AngerManagement::decrease_talent_rank_effect(const QString&, const int) {
    warrior_spells->remove_start_of_combat_spell(this);
}
