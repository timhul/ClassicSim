#include "PolearmSpecialization.h"

#include "CharacterStats.h"
#include "ItemNamespace.h"
#include "Warrior.h"

PolearmSpecialization::PolearmSpecialization(Warrior* warrior, TalentTree* tree_) :
    Talent(warrior, tree_, "Polearm Specialization", "6LL", "Assets/items/Inv_weapon_halbard_01.png", 5) {
    QString base_str = "Increases your chance to get a critical strike with Polearms by %1%.";
    initialize_rank_descriptions(rank_descriptions, base_str, max_points, QVector<QPair<unsigned, unsigned>> {{1, 1}});
}

void PolearmSpecialization::apply_rank_effect() {
    pchar->get_stats()->increase_crit_for_weapon_type(WeaponTypes::POLEARM, 100);
}

void PolearmSpecialization::remove_rank_effect() {
    pchar->get_stats()->decrease_crit_for_weapon_type(WeaponTypes::POLEARM, 100);
}
