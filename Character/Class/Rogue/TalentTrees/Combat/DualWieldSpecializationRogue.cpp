#include "DualWieldSpecializationRogue.h"

#include "OffhandAttackRogue.h"
#include "Rogue.h"
#include "RogueSpells.h"

DualWieldSpecializationRogue::DualWieldSpecializationRogue(Character *pchar, TalentTree* tree) :
    Talent(pchar, tree, "Dual Wield Specialization", "4MR", "Assets/warrior/fury/tier4/Ability_dualwield.png", 5),
    oh_attack(dynamic_cast<OffhandAttackRogue*>(dynamic_cast<RogueSpells*>(dynamic_cast<Rogue*>(pchar)->get_spells())->get_oh_attack()))
{
    QString base_str = "Increases the damage done by your offhand weapon by %1%.";
    initialize_rank_descriptions(base_str, 10, 10);
}

DualWieldSpecializationRogue::~DualWieldSpecializationRogue() = default;

void DualWieldSpecializationRogue::apply_rank_effect() {
    oh_attack->increase_talent_rank(oh_attack, name);
}

void DualWieldSpecializationRogue::remove_rank_effect() {
    oh_attack->decrease_talent_rank(oh_attack, name);
}
