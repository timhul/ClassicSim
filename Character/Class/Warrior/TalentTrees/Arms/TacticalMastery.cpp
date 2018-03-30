
#include "TacticalMastery.h"
#include <QDebug>

TacticalMastery::TacticalMastery(Character *pchar) :
    Talent(pchar, "Tactical Mastery", "2ML", "Assets/warrior/arms/tier2/Spell_nature_enchantarmor.png", 5)
{
    QString base_str = "You retain up to %1 of your rage points when you change stances.";
    initialize_rank_descriptions(base_str, 5, 5);
}

TacticalMastery::~TacticalMastery() {

}

void TacticalMastery::apply_rank_effect() {
    // TODO: Decide how rank effects work for this talent.
}

void TacticalMastery::remove_rank_effect() {
    // TODO: Decide how rank effects work for this talent.
}

QString TacticalMastery::get_requirement_string() const {
    return "Requires 5 points in Arms Talents";
}
