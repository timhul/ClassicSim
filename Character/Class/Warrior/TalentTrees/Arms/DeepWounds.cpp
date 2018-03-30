
#include "DeepWounds.h"
#include <QDebug>

DeepWounds::DeepWounds(Character *pchar) :
    Talent(pchar, "Deep Wounds", "3MR", "Assets/warrior/arms/tier3/Ability_backstab.png", 3)
{
    QString base_str = "Your critical strikes cause the opponent to bleed, dealing %1% of your melee weapon's average damage over 12 sec.";
    initialize_rank_descriptions(base_str, 20, 20);
}

DeepWounds::~DeepWounds() {

}

void DeepWounds::apply_rank_effect() {
    // TODO: Decide how rank effects work for this talent.
}

void DeepWounds::remove_rank_effect() {
    // TODO: Decide how rank effects work for this talent.
}

QString DeepWounds::get_requirement_string() const {
    QString req_string = "";
    if (parent != nullptr && !parent->is_maxed()) {
        req_string = "Requires 3 points in Improved Rend\n";
    }

    // TODO: Req 10 points only valid if user has not spent 10 points.
    return req_string + "Requires 10 points in Arms Talents";
}
