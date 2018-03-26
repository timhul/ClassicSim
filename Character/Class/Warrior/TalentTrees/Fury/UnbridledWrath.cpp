
#include "UnbridledWrath.h"
#include "Character.h"

UnbridledWrath::UnbridledWrath(Character *pchar) :
    Talent(pchar, "Unbridled Wrath", "2MR", "Assets/warrior/fury/tier2/Spell_nature_stoneclawtotem.png", 5)
{
    QString base_str = "Gives you a %1% chance to generate an additional Rage point when you deal melee damage with a weapon.";
    initialize_rank_descriptions(base_str, 8, 8);
}

UnbridledWrath::~UnbridledWrath() {

}

void UnbridledWrath::apply_rank_effect() {
    // TODO: Decide how rank effects work for this talent.
}

void UnbridledWrath::remove_rank_effect() {
    // TODO: Decide how rank effects work for this talent.
}

QString UnbridledWrath::get_requirement_string() const {
    return "Requires 5 points in Fury Talents";
}
