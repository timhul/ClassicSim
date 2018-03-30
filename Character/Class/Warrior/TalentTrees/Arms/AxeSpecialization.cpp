
#include "AxeSpecialization.h"
#include <QDebug>

AxeSpecialization::AxeSpecialization(Character *pchar) :
    Talent(pchar, "Axe Specialization", "5LL", "Assets/warrior/arms/tier5/Inv_axe_06.png", 5)
{
    QString base_str = "Increases your chance to get a critical strike with Axes by %1%.";
    initialize_rank_descriptions(base_str, 1, 1);
}

AxeSpecialization::~AxeSpecialization() {

}

void AxeSpecialization::apply_rank_effect() {
    // TODO: Decide how rank effects work for this talent.
}

void AxeSpecialization::remove_rank_effect() {
    // TODO: Decide how rank effects work for this talent.
}

QString AxeSpecialization::get_requirement_string() const {
    return "Requires 20 points in Arms Talents";
}
