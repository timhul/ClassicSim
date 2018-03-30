
#include "SwordSpecialization.h"
#include <QDebug>

SwordSpecialization::SwordSpecialization(Character *pchar, TalentTree* tree) :
    Talent(pchar, tree, "Sword Specialization", "5RR", "Assets/warrior/arms/tier5/Inv_sword_27.png", 5)
{
    QString base_str = "Gives you a %1% chance to get an extra attack on the same target after dealing damage with your Sword.";
    initialize_rank_descriptions(base_str, 1, 1);
}

SwordSpecialization::~SwordSpecialization() {

}

void SwordSpecialization::apply_rank_effect() {
    // TODO: Decide how rank effects work for this talent.
}

void SwordSpecialization::remove_rank_effect() {
    // TODO: Decide how rank effects work for this talent.
}
