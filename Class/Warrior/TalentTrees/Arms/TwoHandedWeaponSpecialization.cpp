#include "TwoHandedWeaponSpecialization.h"

#include "Character.h"
#include "CharacterStats.h"
#include "ItemNamespace.h"

TwoHandedWeaponSpecialization::TwoHandedWeaponSpecialization(Character *pchar, TalentTree* tree) :
    Talent(pchar, tree, "Two-Handed Weapon Specialization", "4ML", "Assets/items/Inv_axe_09.png", 5)
{
    QString base_str = "Increases the damage you deal with two-handed melee weapons by %1%.";
    initialize_rank_descriptions(rank_descriptions, base_str, max_points, QVector<QPair<unsigned, unsigned>>{{1, 1}});

    talent_ranks = {0, 1, 2, 3, 4, 5};
    affected_weapon_types = QSet<int>({WeaponTypes::TWOHAND_AXE,
                                       WeaponTypes::TWOHAND_MACE,
                                       WeaponTypes::TWOHAND_SWORD,
                                       WeaponTypes::POLEARM,
                                       WeaponTypes::STAFF});
}

TwoHandedWeaponSpecialization::~TwoHandedWeaponSpecialization() = default;

void TwoHandedWeaponSpecialization::apply_rank_effect() {
    for (const auto & weapon_type : affected_weapon_types) {
        if (curr_points != 1)
            pchar->get_stats()->decrease_total_phys_dmg_for_weapon_type(weapon_type, talent_ranks[static_cast<int>(curr_points)  - 1]);

        pchar->get_stats()->increase_total_phys_dmg_for_weapon_type(weapon_type, talent_ranks[static_cast<int>(curr_points)]);
    }
}

void TwoHandedWeaponSpecialization::remove_rank_effect() {
    int delta = talent_ranks[static_cast<int>(curr_points) + 1] - talent_ranks[static_cast<int>(curr_points)];
    for (const auto & weapon_type : affected_weapon_types) {
        pchar->get_stats()->decrease_total_phys_dmg_for_weapon_type(weapon_type, delta);
    }
}
