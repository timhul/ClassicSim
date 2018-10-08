
#include "ImprovedSlam.h"
#include "Slam.h"
#include "Warrior.h"
#include "WarriorSpells.h"

ImprovedSlam::ImprovedSlam(Character *pchar, TalentTree* tree) :
    Talent(pchar, tree, "Improved Slam", "5LL", "Assets/warrior/fury/tier5/Ability_warrior_decisivestrike.png", 5)
{
    QString base_str = "Decreases the casting time of your Slam ability by 0.%1 sec.";
    initialize_rank_descriptions(base_str, 1, 1);
}

ImprovedSlam::~ImprovedSlam() = default;

void ImprovedSlam::apply_rank_effect() {
    auto* warr = dynamic_cast<Warrior*>(pchar);
    dynamic_cast<WarriorSpells*>(warr->get_spells())->get_slam()->increase_effect_via_talent();
}

void ImprovedSlam::remove_rank_effect() {
    auto* warr = dynamic_cast<Warrior*>(pchar);
    dynamic_cast<WarriorSpells*>(warr->get_spells())->get_slam()->decrease_effect_via_talent();
}
