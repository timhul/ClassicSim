
#include "ImprovedBerserkerRage.h"
#include "BerserkerRage.h"
#include "Warrior.h"

ImprovedBerserkerRage::ImprovedBerserkerRage(Character *pchar, TalentTree* tree) :
    Talent(pchar, tree,  "Improved Berserker Rage", "6LL", "Assets/warrior/fury/tier6/Spell_nature_ancestralguardian.png", 2)
{
    QString base_str = "The Berserker Rage ability will generate %1 rage when used.";
    initialize_rank_descriptions(base_str, 5, 5);
}

ImprovedBerserkerRage::~ImprovedBerserkerRage() {

}

void ImprovedBerserkerRage::apply_rank_effect() {
    dynamic_cast<Warrior*>(pchar)->get_berserker_rage()->increase_effect_via_talent();
}

void ImprovedBerserkerRage::remove_rank_effect() {
    dynamic_cast<Warrior*>(pchar)->get_berserker_rage()->decrease_effect_via_talent();
}
