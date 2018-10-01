
#include "ImprovedHeroicStrike.h"
#include "HeroicStrike.h"
#include "Warrior.h"
#include "WarriorSpells.h"

ImprovedHeroicStrike::ImprovedHeroicStrike(Character *pchar, TalentTree* tree) :
    Talent(pchar, tree, "Improved Heroic Strike", "1LL", "Assets/warrior/arms/tier1/Ability_rogue_ambush.png", 3)
{
    QString base_str = "Reduces the cost of your Heroic Strike ability by %1 rage.";
    initialize_rank_descriptions(base_str, 1, 1);
}

ImprovedHeroicStrike::~ImprovedHeroicStrike() = default;

void ImprovedHeroicStrike::apply_rank_effect() {
    // TODO: Create WarriorTalent that has warrior available.
    auto* warr = dynamic_cast<Warrior*>(pchar);
    dynamic_cast<WarriorSpells*>(warr->get_spells())->get_heroic_strike()->increase_effect_via_talent();
}

void ImprovedHeroicStrike::remove_rank_effect() {
    // TODO: Create WarriorTalent that has warrior available.
    auto* warr = dynamic_cast<Warrior*>(pchar);
    dynamic_cast<WarriorSpells*>(warr->get_spells())->get_heroic_strike()->decrease_effect_via_talent();
}
