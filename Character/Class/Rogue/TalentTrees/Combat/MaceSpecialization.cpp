#include "MaceSpecialization.h"

#include "Character.h"
#include "CharacterStats.h"
#include "ItemNamespace.h"

MaceSpecialization::MaceSpecialization(Character *pchar, TalentTree* tree) :
    Talent(pchar, tree, "Mace Specialization", "5LL", "Assets/items/Inv_mace_01.png", 5)
{
    QString base_str = "Increases your skill with Maces by %1, and gives you a %2% chance to stun your target for 3 sec with a mace.";
    initialize_rank_descriptions(base_str, 1, 1);
}

MaceSpecialization::~MaceSpecialization() = default;

void MaceSpecialization::apply_rank_effect() {
    pchar->get_stats()->increase_wpn_skill(WeaponTypes::MACE, 1);
    pchar->get_stats()->increase_wpn_skill(WeaponTypes::TWOHAND_MACE, 1);
}

void MaceSpecialization::remove_rank_effect() {
    pchar->get_stats()->decrease_wpn_skill(WeaponTypes::MACE, 1);
    pchar->get_stats()->decrease_wpn_skill(WeaponTypes::TWOHAND_MACE, 1);
}
