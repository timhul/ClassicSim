#include "SwordSpecializationTalentRogue.h"

#include "SwordSpecialization.h"
#include "Rogue.h"

SwordSpecializationTalentRogue::SwordSpecializationTalentRogue(Character *pchar, TalentTree* tree) :
    Talent(pchar, tree, "Sword Specialization", "5MR", "Assets/items/Inv_sword_27.png", 5),
    sword_spec(dynamic_cast<Rogue*>(pchar)->get_sword_spec())
{
    QString base_str = "Gives you a %1% chance to get an extra attack on the same target after dealing damage with your Sword.";
    initialize_rank_descriptions(base_str, 1, 1);
}

SwordSpecializationTalentRogue::~SwordSpecializationTalentRogue() = default;

void SwordSpecializationTalentRogue::apply_rank_effect() {
    sword_spec->increase_talent_rank(sword_spec, name);
}

void SwordSpecializationTalentRogue::remove_rank_effect() {
    sword_spec->decrease_talent_rank(sword_spec, name);
}
