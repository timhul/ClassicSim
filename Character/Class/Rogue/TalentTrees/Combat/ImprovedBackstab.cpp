#include "ImprovedBackstab.h"

#include "Backstab.h"
#include "Rogue.h"
#include "RogueSpells.h"

ImprovedBackstab::ImprovedBackstab(Character *pchar, TalentTree* tree) :
    Talent(pchar, tree, "Improved Backstab", "2LL", "Assets/ability/Ability_backstab.png", 3),
    backstab(dynamic_cast<RogueSpells*>(dynamic_cast<Rogue*>(pchar)->get_spells())->get_backstab())
{
    QString base_str = "Increases the critical strike chance of your Backstab ability by %1%.";
    initialize_rank_descriptions(base_str, 10, 10);
}

void ImprovedBackstab::apply_rank_effect() {
    backstab->increase_talent_rank(backstab, name);
}

void ImprovedBackstab::remove_rank_effect() {
    backstab->decrease_talent_rank(backstab, name);
}
