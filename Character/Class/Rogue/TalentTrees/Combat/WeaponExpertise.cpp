#include "WeaponExpertise.h"

#include "Character.h"
#include "CharacterStats.h"
#include "ItemNamespace.h"

WeaponExpertise::WeaponExpertise(Character *pchar, TalentTree* tree) :
    Talent(pchar, tree, "Weapon Expertise", "6ML", "Assets/spell/Spell_holy_blessingofstrength.png", 2)
{
    QString base_str = "Increases your skill with Sword, Fist and Dagger weapons by %1.";
    initialize_rank_descriptions(base_str, 3, 2);
}

WeaponExpertise::~WeaponExpertise() = default;

void WeaponExpertise::apply_rank_effect() {
    const int increase = curr_points == 1 ? 3 : 2;

    pchar->get_stats()->increase_wpn_skill(WeaponTypes::DAGGER, increase);
    pchar->get_stats()->increase_wpn_skill(WeaponTypes::FIST, increase);
    pchar->get_stats()->increase_wpn_skill(WeaponTypes::SWORD, increase);
    pchar->get_stats()->increase_wpn_skill(WeaponTypes::TWOHAND_SWORD, increase);
}

void WeaponExpertise::remove_rank_effect() {
    const int decrease = curr_points == 1 ? 2 : 3;

    pchar->get_stats()->decrease_wpn_skill(WeaponTypes::DAGGER, decrease);
    pchar->get_stats()->decrease_wpn_skill(WeaponTypes::FIST, decrease);
    pchar->get_stats()->decrease_wpn_skill(WeaponTypes::SWORD, decrease);
    pchar->get_stats()->decrease_wpn_skill(WeaponTypes::TWOHAND_SWORD, decrease);
}
