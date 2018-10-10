
#include "DeepWoundsTalent.h"
#include "DeepWounds.h"
#include "Warrior.h"
#include "WarriorSpells.h"

DeepWoundsTalent::DeepWoundsTalent(Character *pchar, TalentTree* tree) :
    Talent(pchar, tree, "Deep Wounds", "3MR", "Assets/warrior/arms/tier3/Ability_backstab.png", 3),
    deep_wounds( dynamic_cast<WarriorSpells*>(dynamic_cast<Warrior*>(pchar)->get_spells())->get_deep_wounds())
{
    QString base_str = "Your critical strikes cause the opponent to bleed, dealing %1% of your melee weapon's average damage over 12 sec.";
    initialize_rank_descriptions(base_str, 20, 20);
}

DeepWoundsTalent::~DeepWoundsTalent() = default;

void DeepWoundsTalent::apply_rank_effect() {
    deep_wounds->increase_talent_rank(deep_wounds);
}

void DeepWoundsTalent::remove_rank_effect() {
    deep_wounds->decrease_talent_rank(deep_wounds);
}
