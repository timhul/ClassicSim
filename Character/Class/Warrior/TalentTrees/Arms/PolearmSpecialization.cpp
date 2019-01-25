
#include "PolearmSpecialization.h"
#include "Warrior.h"
#include "CharacterStats.h"
#include "ItemNamespace.h"

PolearmSpecialization::PolearmSpecialization(Character *pchar, TalentTree* tree) :
    Talent(pchar, tree, "Polearm Specialization", "6LL", "Assets/items/Inv_weapon_halbard_01.png", 5)
{
    QString base_str = "Increases your chance to get a critical strike with Polearms by %1%.";
    initialize_rank_descriptions(rank_descriptions, base_str, max_points, QVector<QPair<int, int>>{{1, 1}});
}

PolearmSpecialization::~PolearmSpecialization() = default;

void PolearmSpecialization::apply_rank_effect() {
    dynamic_cast<Warrior*>(pchar)->get_stats()->increase_crit_for_weapon_type(WeaponTypes::POLEARM, 0.01);
}

void PolearmSpecialization::remove_rank_effect() {
    dynamic_cast<Warrior*>(pchar)->get_stats()->decrease_crit_for_weapon_type(WeaponTypes::POLEARM, 0.01);
}
