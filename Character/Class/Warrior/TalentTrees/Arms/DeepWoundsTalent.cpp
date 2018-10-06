
#include "DeepWoundsTalent.h"
#include "DeepWounds.h"
#include "Warrior.h"
#include "WarriorSpells.h"

DeepWoundsTalent::DeepWoundsTalent(Character *pchar, TalentTree* tree) :
    Talent(pchar, tree, "Deep Wounds", "3MR", "Assets/warrior/arms/tier3/Ability_backstab.png", 3)
{
    QString base_str = "Your critical strikes cause the opponent to bleed, dealing %1% of your melee weapon's average damage over 12 sec.";
    initialize_rank_descriptions(base_str, 20, 20);
}

DeepWoundsTalent::~DeepWoundsTalent() = default;

void DeepWoundsTalent::apply_rank_effect() {
    auto* warr = dynamic_cast<Warrior*>(pchar);
    dynamic_cast<WarriorSpells*>(warr->get_spells())->get_deep_wounds()->increase_effect_via_talent();
}

void DeepWoundsTalent::remove_rank_effect() {
    auto* warr = dynamic_cast<Warrior*>(pchar);
    dynamic_cast<WarriorSpells*>(warr->get_spells())->get_deep_wounds()->decrease_effect_via_talent();
}
