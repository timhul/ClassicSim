
#include "ImprovedOverpower.h"
#include "Overpower.h"
#include "Warrior.h"
#include "WarriorSpells.h"

ImprovedOverpower::ImprovedOverpower(Character *pchar, TalentTree* tree) :
    Talent(pchar, tree, "Improved Overpower", "3LL", "Assets/warrior/arms/tier3/Inv_sword_05.png", 2)
{
    QString base_str = "Increase the critical strike chance of your Overpower ability by %1%.";
    initialize_rank_descriptions(base_str, 25, 25);
}

ImprovedOverpower::~ImprovedOverpower() {

}

void ImprovedOverpower::apply_rank_effect() {
    // TODO: Create WarriorTalent that has warrior available.
    Warrior* warr = dynamic_cast<Warrior*>(pchar);
    dynamic_cast<WarriorSpells*>(warr->get_spells())->get_overpower()->increase_effect_via_talent();
}

void ImprovedOverpower::remove_rank_effect() {
    // TODO: Create WarriorTalent that has warrior available.
    Warrior* warr = dynamic_cast<Warrior*>(pchar);
    dynamic_cast<WarriorSpells*>(warr->get_spells())->get_overpower()->decrease_effect_via_talent();
}
