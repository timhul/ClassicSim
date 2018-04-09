
#include "UnbridledWrathTalent.h"
#include "UnbridledWrath.h"
#include "Warrior.h"

UnbridledWrathTalent::UnbridledWrathTalent(Character *pchar, TalentTree* tree) :
    Talent(pchar, tree, "Unbridled Wrath", "2MR", "Assets/warrior/fury/tier2/Spell_nature_stoneclawtotem.png", 5)
{
    QString base_str = "Gives you a %1% chance to generate an additional Rage point when you deal melee damage with a weapon.";
    initialize_rank_descriptions(base_str, 8, 8);
}

UnbridledWrathTalent::~UnbridledWrathTalent() {

}

void UnbridledWrathTalent::apply_rank_effect() {
    dynamic_cast<Warrior*>(pchar)->get_unbridled_wrath()->increase_effect_via_talent();
}

void UnbridledWrathTalent::remove_rank_effect() {
    dynamic_cast<Warrior*>(pchar)->get_unbridled_wrath()->decrease_effect_via_talent();
}
