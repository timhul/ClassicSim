
#include "ImprovedCleave.h"
#include "Character.h"

ImprovedCleave::ImprovedCleave(Character *pchar) :
    Talent(pchar, "Improved Cleave", "3LL", "Assets/warrior/fury/tier3/Ability_warrior_cleave.png", 3)
{
    QString base_str = "Increases the bonus damage done by your Cleave ability by %1%.";
    initialize_rank_descriptions(base_str, 40, 40);
}

ImprovedCleave::~ImprovedCleave() {

}

void ImprovedCleave::apply_rank_effect() {
    // TODO: Decide how rank effects work for this talent.
}

void ImprovedCleave::remove_rank_effect() {
    // TODO: Decide how rank effects work for this talent.
}

QString ImprovedCleave::get_requirement_string() const {
    return "Requires 10 points in Fury Talents";
}
