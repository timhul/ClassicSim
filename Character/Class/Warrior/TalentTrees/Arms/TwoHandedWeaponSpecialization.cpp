
#include "TwoHandedWeaponSpecialization.h"
#include <QDebug>

TwoHandedWeaponSpecialization::TwoHandedWeaponSpecialization(Character *pchar) :
    Talent(pchar, "Two-Handed Weapon Specialization", "4ML", "Assets/warrior/arms/tier4/Inv_axe_09.png", 5)
{
    QString base_str = "Increases the damage you deal with two-handed melee weapons by %1%.";
    initialize_rank_descriptions(base_str, 1, 1);
}

TwoHandedWeaponSpecialization::~TwoHandedWeaponSpecialization() {

}

void TwoHandedWeaponSpecialization::apply_rank_effect() {
    // TODO: Decide how rank effects work for this talent.
}

void TwoHandedWeaponSpecialization::remove_rank_effect() {
    // TODO: Decide how rank effects work for this talent.
}

QString TwoHandedWeaponSpecialization::get_requirement_string() const {
    return "Requires 15 points in Arms Talents";
}
