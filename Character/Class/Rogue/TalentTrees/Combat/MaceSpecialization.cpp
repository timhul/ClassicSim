#include "MaceSpecialization.h"

#include "Character.h"
#include "CharacterStats.h"
#include "ItemNamespace.h"

MaceSpecialization::MaceSpecialization(Character *pchar, TalentTree* tree) :
    Talent(pchar, tree, "Mace Specialization", "5LL", "Assets/items/Inv_mace_01.png", 5)
{
    QString base_str = "Increases your skill with Maces by %1, and gives you a %2% chance to stun your target for 3 sec with a mace.";
    rank_descriptions.insert(0, base_str.arg(1).arg(1));
    rank_descriptions.insert(1, base_str.arg(1).arg(1));
    rank_descriptions.insert(2, base_str.arg(2).arg(2));
    rank_descriptions.insert(3, base_str.arg(3).arg(3));
    rank_descriptions.insert(4, base_str.arg(4).arg(4));
    rank_descriptions.insert(5, base_str.arg(5).arg(6));
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
