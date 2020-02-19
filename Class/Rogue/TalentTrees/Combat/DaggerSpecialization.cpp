#include "DaggerSpecialization.h"

#include "CharacterStats.h"
#include "ItemNamespace.h"
#include "Rogue.h"

DaggerSpecialization::DaggerSpecialization(Character* pchar, TalentTree* tree) :
    Talent(pchar, tree, "Dagger Specialization", "4ML", "Assets/items/Inv_weapon_shortblade_05.png", 5) {
    QString base_str = "Increases your chance to get a critical strike with Daggers by %1%.";
    initialize_rank_descriptions(rank_descriptions, base_str, max_points, QVector<QPair<unsigned, unsigned>> {{1, 1}});
}

DaggerSpecialization::~DaggerSpecialization() = default;

void DaggerSpecialization::apply_rank_effect() {
    pchar->get_stats()->increase_crit_for_weapon_type(WeaponTypes::DAGGER, 100);
}

void DaggerSpecialization::remove_rank_effect() {
    pchar->get_stats()->decrease_crit_for_weapon_type(WeaponTypes::DAGGER, 100);
}
