
#include "ImprovedHeroicStrike.h"
#include "HeroicStrike.h"
#include "Warrior.h"
#include "WarriorSpells.h"

ImprovedHeroicStrike::ImprovedHeroicStrike(Character *pchar, TalentTree* tree) :
    Talent(pchar, tree, "Improved Heroic Strike", "1LL", "Assets/warrior/arms/tier1/Ability_rogue_ambush.png", 3),
    heroic_strike(dynamic_cast<WarriorSpells*>(dynamic_cast<Warrior*>(pchar)->get_spells())->get_heroic_strike())
{
    QString base_str = "Reduces the cost of your Heroic Strike ability by %1 rage.";
    initialize_rank_descriptions(base_str, 1, 1);
}

ImprovedHeroicStrike::~ImprovedHeroicStrike() = default;

void ImprovedHeroicStrike::apply_rank_effect() {
    heroic_strike->increase_talent_rank(heroic_strike);
}

void ImprovedHeroicStrike::remove_rank_effect() {
    heroic_strike->decrease_talent_rank(heroic_strike);
}
