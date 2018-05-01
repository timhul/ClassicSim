
#include "DualWieldSpecialization.h"
#include "OffhandAttackWarrior.h"
#include "Warrior.h"
#include "WarriorSpells.h"

DualWieldSpecialization::DualWieldSpecialization(Character *pchar, TalentTree* tree) :
    Talent(pchar, tree, "Dual Wield Specialization", "4LL", "Assets/warrior/fury/tier4/Ability_dualwield.png", 5)
{
    QString base_str = "Increases the damage done by your offhand weapon by %1%.";
    initialize_rank_descriptions(base_str, 5, 5);
}

DualWieldSpecialization::~DualWieldSpecialization() {

}

void DualWieldSpecialization::apply_rank_effect() {
    // TODO: Create WarriorTalent that has warrior available.
    Warrior* warr = dynamic_cast<Warrior*>(pchar);
    dynamic_cast<WarriorSpells*>(warr->get_spells())->get_oh_attack_warrior()->increase_effect_via_talent();
}

void DualWieldSpecialization::remove_rank_effect() {
    // TODO: Create WarriorTalent that has warrior available.
    Warrior* warr = dynamic_cast<Warrior*>(pchar);
    dynamic_cast<WarriorSpells*>(warr->get_spells())->get_oh_attack_warrior()->decrease_effect_via_talent();
}
