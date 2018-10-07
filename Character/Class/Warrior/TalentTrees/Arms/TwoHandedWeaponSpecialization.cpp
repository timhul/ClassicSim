
#include "TwoHandedWeaponSpecialization.h"
#include "Character.h"
#include "CharacterStats.h"
#include "ItemNamespace.h"

TwoHandedWeaponSpecialization::TwoHandedWeaponSpecialization(Character *pchar, TalentTree* tree) :
    Talent(pchar, tree, "Two-Handed Weapon Specialization", "4ML", "Assets/warrior/arms/tier4/Inv_axe_09.png", 5)
{
    QString base_str = "Increases the damage you deal with two-handed melee weapons by %1%.";
    initialize_rank_descriptions(base_str, 1, 1);

    talent_ranks = {0, 1, 2, 3, 4, 5};
    affected_weapon_types = QSet<int>({WeaponTypes::TWOHAND_AXE,
                                       WeaponTypes::TWOHAND_MACE,
                                       WeaponTypes::TWOHAND_SWORD,
                                       WeaponTypes::POLEARM,
                                       WeaponTypes::STAFF});
}

TwoHandedWeaponSpecialization::~TwoHandedWeaponSpecialization() = default;

void TwoHandedWeaponSpecialization::apply_rank_effect() {
    for (auto & weapon_type : affected_weapon_types) {
        if (curr_points != 0)
            pchar->get_stats()->decrease_total_phys_dmg_for_weapon_type(weapon_type, talent_ranks[curr_points]);

        pchar->get_stats()->increase_total_phys_dmg_for_weapon_type(weapon_type, talent_ranks[curr_points + 1]);
    }
}

void TwoHandedWeaponSpecialization::remove_rank_effect() {
    int delta = talent_ranks[curr_points] - talent_ranks[curr_points - 1];
    for (auto & weapon_type : affected_weapon_types) {
        pchar->get_stats()->decrease_total_phys_dmg_for_weapon_type(weapon_type, delta);
    }
}
