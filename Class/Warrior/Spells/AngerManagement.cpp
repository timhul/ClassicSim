#include "AngerManagement.h"

#include "Resource.h"
#include "Utils/Check.h"
#include "Warrior.h"
#include "WarriorSpells.h"

AngerManagement::AngerManagement(Character* pchar) :
    PeriodicResourceGainSpell("Anger Management", "Assets/spell/Spell_holy_blessingofstamina.png", pchar, RestrictedByGcd::No, 3.0,
                              std::numeric_limits<int>::max(), {{ResourceType::Rage, 1}}),
    TalentRequirer(QVector<TalentRequirerInfo*>{new TalentRequirerInfo("Anger Management", 1, DisabledAtZero::Yes)}),
    warr(dynamic_cast<Warrior*>(pchar))
{
    this->enabled = false;
}

void AngerManagement::perform_start_of_combat() {
    perform();
}

void AngerManagement::increase_talent_rank_effect(const QString&, const int) {
    dynamic_cast<WarriorSpells*>(warr->get_spells())->add_start_of_combat_spell(this);
}

void AngerManagement::decrease_talent_rank_effect(const QString&, const int) {
    dynamic_cast<WarriorSpells*>(warr->get_spells())->remove_start_of_combat_spell(this);
}
