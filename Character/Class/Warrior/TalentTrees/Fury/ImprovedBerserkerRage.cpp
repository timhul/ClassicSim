
#include "ImprovedBerserkerRage.h"
#include "Character.h"

ImprovedBerserkerRage::ImprovedBerserkerRage(Character *pchar, TalentTree* tree) :
    Talent(pchar, tree,  "Improved Berserker Rage", "6LL", "Assets/warrior/fury/tier6/Spell_nature_ancestralguardian.png", 2)
{
    QString base_str = "The Berserker Rage ability will generate %1 rage when used.";
    initialize_rank_descriptions(base_str, 5, 5);
}

ImprovedBerserkerRage::~ImprovedBerserkerRage() {

}

void ImprovedBerserkerRage::apply_rank_effect() {
    // TODO: Decide how rank effects work for this talent.
}

void ImprovedBerserkerRage::remove_rank_effect() {
    // TODO: Decide how rank effects work for this talent.
}
