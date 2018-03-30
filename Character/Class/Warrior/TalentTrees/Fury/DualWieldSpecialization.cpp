
#include "DualWieldSpecialization.h"
#include "Character.h"

DualWieldSpecialization::DualWieldSpecialization(Character *pchar, TalentTree* tree) :
    Talent(pchar, tree, "Dual Wield Specialization", "4LL", "Assets/warrior/fury/tier4/Ability_dualwield.png", 5)
{
    QString base_str = "Increases the damage done by your offhand weapon by %1%.";
    initialize_rank_descriptions(base_str, 5, 5);
}

DualWieldSpecialization::~DualWieldSpecialization() {

}

void DualWieldSpecialization::apply_rank_effect() {
    // TODO: Decide how rank effects work for this talent.
}

void DualWieldSpecialization::remove_rank_effect() {
    // TODO: Decide how rank effects work for this talent.
}
