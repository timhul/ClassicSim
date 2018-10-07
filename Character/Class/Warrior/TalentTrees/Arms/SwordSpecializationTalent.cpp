
#include "SwordSpecializationTalent.h"
#include "SwordSpecialization.h"
#include "Warrior.h"

SwordSpecializationTalent::SwordSpecializationTalent(Character *pchar, TalentTree* tree) :
    Talent(pchar, tree, "Sword Specialization", "5RR", "Assets/warrior/arms/tier5/Inv_sword_27.png", 5)
{
    QString base_str = "Gives you a %1% chance to get an extra attack on the same target after dealing damage with your Sword.";
    initialize_rank_descriptions(base_str, 1, 1);
}

SwordSpecializationTalent::~SwordSpecializationTalent() = default;

void SwordSpecializationTalent::apply_rank_effect() {
    dynamic_cast<Warrior*>(pchar)->get_sword_spec()->increase_effect_via_talent();
}

void SwordSpecializationTalent::remove_rank_effect() {
    dynamic_cast<Warrior*>(pchar)->get_sword_spec()->decrease_effect_via_talent();
}
