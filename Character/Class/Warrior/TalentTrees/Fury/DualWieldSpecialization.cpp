
#include "DualWieldSpecialization.h"
#include "OffhandAttackWarrior.h"
#include "Warrior.h"
#include "WarriorSpells.h"

DualWieldSpecialization::DualWieldSpecialization(Character *pchar, TalentTree* tree) :
    Talent(pchar, tree, "Dual Wield Specialization", "4LL", "Assets/warrior/fury/tier4/Ability_dualwield.png", 5),
    oh_attack(dynamic_cast<WarriorSpells*>(dynamic_cast<Warrior*>(pchar)->get_spells())->get_oh_attack_warrior())
{
    QString base_str = "Increases the damage done by your offhand weapon by %1%.";
    initialize_rank_descriptions(base_str, 5, 5);
}

DualWieldSpecialization::~DualWieldSpecialization() = default;

void DualWieldSpecialization::apply_rank_effect() {
    oh_attack->increase_talent_rank(oh_attack, name);
}

void DualWieldSpecialization::remove_rank_effect() {
    oh_attack->decrease_talent_rank(oh_attack, name);
}
