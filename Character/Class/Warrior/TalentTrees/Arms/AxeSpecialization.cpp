
#include "AxeSpecialization.h"
#include "Warrior.h"
#include "CharacterStats.h"
#include "ItemNamespace.h"

AxeSpecialization::AxeSpecialization(Character *pchar, TalentTree* tree) :
    Talent(pchar, tree, "Axe Specialization", "5LL", "Assets/warrior/arms/tier5/Inv_axe_06.png", 5)
{
    QString base_str = "Increases your chance to get a critical strike with Axes by %1%.";
    initialize_rank_descriptions(base_str, 1, 1);
}

AxeSpecialization::~AxeSpecialization() = default;

void AxeSpecialization::apply_rank_effect() {
    dynamic_cast<Warrior*>(pchar)->get_stats()->increase_crit_for_weapon_type(WeaponTypes::AXE, 0.01);
}

void AxeSpecialization::remove_rank_effect() {
    dynamic_cast<Warrior*>(pchar)->get_stats()->decrease_crit_for_weapon_type(WeaponTypes::AXE, 0.01);
}
