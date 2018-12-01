#include "FistWeaponSpecialization.h"

#include "Character.h"
#include "CharacterStats.h"
#include "ItemNamespace.h"

FistWeaponSpecialization::FistWeaponSpecialization(Character *pchar, TalentTree* tree) :
    Talent(pchar, tree, "Fist Weapon Specialization", "5RR", "Assets/items/Inv_gauntlets_04.png", 5)
{
    QString base_str = "Increases your chance to get a critical strike with Fist Weapons by %1%.";
    initialize_rank_descriptions(base_str, 1, 1);
}

FistWeaponSpecialization::~FistWeaponSpecialization() = default;

void FistWeaponSpecialization::apply_rank_effect() {
    pchar->get_stats()->increase_crit_for_weapon_type(WeaponTypes::FIST, 0.01);
}

void FistWeaponSpecialization::remove_rank_effect() {
    pchar->get_stats()->decrease_crit_for_weapon_type(WeaponTypes::FIST, 0.01);
}
