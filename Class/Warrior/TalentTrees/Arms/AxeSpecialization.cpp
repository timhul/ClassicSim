#include "AxeSpecialization.h"

#include "CharacterStats.h"
#include "ItemNamespace.h"
#include "Warrior.h"

AxeSpecialization::AxeSpecialization(Warrior* warrior, TalentTree* tree_) :
    Talent(warrior, tree_, "Axe Specialization", "5LL", "Assets/items/Inv_axe_06.png", 5)
{
    QString base_str = "Increases your chance to get a critical strike with Axes by %1%.";
    initialize_rank_descriptions(rank_descriptions, base_str, max_points, QVector<QPair<unsigned, unsigned>>{{1, 1}});
}

void AxeSpecialization::apply_rank_effect() {
    pchar->get_stats()->increase_crit_for_weapon_type(WeaponTypes::AXE, 100);
}

void AxeSpecialization::remove_rank_effect() {
    pchar->get_stats()->decrease_crit_for_weapon_type(WeaponTypes::AXE, 100);
}
