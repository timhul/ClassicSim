
#include "ImprovedOverpower.h"
#include "Overpower.h"
#include "Warrior.h"
#include "WarriorSpells.h"

ImprovedOverpower::ImprovedOverpower(Character *pchar, TalentTree* tree) :
    Talent(pchar, tree, "Improved Overpower", "3LL", "Assets/items/Inv_sword_05.png", 2),
    overpower(dynamic_cast<WarriorSpells*>(dynamic_cast<Warrior*>(pchar)->get_spells())->get_overpower())
{
    QString base_str = "Increase the critical strike chance of your Overpower ability by %1%.";
    initialize_rank_descriptions(base_str, 25, 25);
}

ImprovedOverpower::~ImprovedOverpower() = default;

void ImprovedOverpower::apply_rank_effect() {
    overpower->increase_talent_rank(overpower, name);
}

void ImprovedOverpower::remove_rank_effect() {
    overpower->decrease_talent_rank(overpower, name);
}
