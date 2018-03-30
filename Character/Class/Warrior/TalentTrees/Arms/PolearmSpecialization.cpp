
#include "PolearmSpecialization.h"
#include <QDebug>

PolearmSpecialization::PolearmSpecialization(Character *pchar, TalentTree* tree) :
    Talent(pchar, tree, "Polearm Specialization", "6LL", "Assets/warrior/arms/tier6/Inv_weapon_halbard_01.png", 5)
{
    QString base_str = "Increases your chance to get a critical strike with Polearms by %1%.";
    initialize_rank_descriptions(base_str, 1, 1);
}

PolearmSpecialization::~PolearmSpecialization() {

}

void PolearmSpecialization::apply_rank_effect() {
    // TODO: Decide how rank effects work for this talent.
}

void PolearmSpecialization::remove_rank_effect() {
    // TODO: Decide how rank effects work for this talent.
}
