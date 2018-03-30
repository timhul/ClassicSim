
#include "Impale.h"
#include <QDebug>

Impale::Impale(Character *pchar) :
    Talent(pchar, "Impale", "4MR", "Assets/warrior/arms/tier4/Ability_searingarrow.png", 2)
{
    QString base_str = "Increases the critical strike damage bonus of your abilities in Battle, Defensive, and Berserker stance by %1%.";
    initialize_rank_descriptions(base_str, 10, 10);
}

Impale::~Impale() {

}

void Impale::apply_rank_effect() {
    // TODO: Decide how rank effects work for this talent.
}

void Impale::remove_rank_effect() {
    // TODO: Decide how rank effects work for this talent.
}

QString Impale::get_requirement_string() const {
    QString req_string = "";
    if (parent != nullptr && !parent->is_maxed()) {
        req_string = "Requires 3 points in Deep Wounds\n";
    }

    // TODO: Req 10 points only valid if user has not spent 15 points.
    return req_string + "Requires 15 points in Arms Talents";
}
