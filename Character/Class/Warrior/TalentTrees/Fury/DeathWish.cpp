
#include "DeathWish.h"
#include "Character.h"

DeathWish::DeathWish(Character *pchar) :
    Talent(pchar, "Death Wish", "5ML", "Assets/warrior/fury/tier5/Spell_shadow_deathpact.png", 1)
{
    QString base_str = "When activated, increases your physical damage by 20% and makes you immune to Fear effects, but lowers your armor and all resistances by 20%. Lasts 30 sec.";
    rank_descriptions.insert(0, base_str);
    rank_descriptions.insert(1, base_str);
}

DeathWish::~DeathWish() {

}

void DeathWish::apply_rank_effect() {
    // TODO: Decide how rank effects work for this talent.
}

void DeathWish::remove_rank_effect() {
    // TODO: Decide how rank effects work for this talent.
}

QString DeathWish::get_requirement_string() const {
    return "Requires 20 points in Fury Talents";
}
