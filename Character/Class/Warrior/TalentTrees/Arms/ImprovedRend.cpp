
#include "ImprovedRend.h"
#include "Rend.h"
#include "Warrior.h"
#include "WarriorSpells.h"

ImprovedRend::ImprovedRend(Character *pchar, TalentTree* tree) :
    Talent(pchar, tree, "Improved Rend", "1MR", "Assets/warrior/arms/tier1/Ability_gouge.png", 3),
    rend(dynamic_cast<WarriorSpells*>(dynamic_cast<Warrior*>(pchar)->get_spells())->get_rend())
{
    QString base_str = "Increases the bleed damage done by your Rend ability by %1%.";
    initialize_rank_descriptions(base_str, 15, 10);
}

ImprovedRend::~ImprovedRend() = default;

void ImprovedRend::apply_rank_effect() {
    rend->increase_talent_rank(rend, name);
}

void ImprovedRend::remove_rank_effect() {
    rend->decrease_talent_rank(rend, name);
}
