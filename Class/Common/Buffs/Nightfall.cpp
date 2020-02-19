#include "Nightfall.h"

#include "Character.h"
#include "Target.h"

Nightfall::Nightfall(Character* pchar) : SharedDebuff(pchar, "Nightfall", "Assets/items/Inv_axe_12.png", Priority::Low, 5, 0) {}

void Nightfall::buff_effect_when_applied() {
    pchar->get_target()->increase_magic_school_damage_mod(15, MagicSchool::Arcane);
    pchar->get_target()->increase_magic_school_damage_mod(15, MagicSchool::Fire);
    pchar->get_target()->increase_magic_school_damage_mod(15, MagicSchool::Frost);
    pchar->get_target()->increase_magic_school_damage_mod(15, MagicSchool::Holy);
    pchar->get_target()->increase_magic_school_damage_mod(15, MagicSchool::Nature);
    pchar->get_target()->increase_magic_school_damage_mod(15, MagicSchool::Shadow);
}

void Nightfall::buff_effect_when_removed() {
    pchar->get_target()->decrease_magic_school_damage_mod(15, MagicSchool::Arcane);
    pchar->get_target()->decrease_magic_school_damage_mod(15, MagicSchool::Fire);
    pchar->get_target()->decrease_magic_school_damage_mod(15, MagicSchool::Frost);
    pchar->get_target()->decrease_magic_school_damage_mod(15, MagicSchool::Holy);
    pchar->get_target()->decrease_magic_school_damage_mod(15, MagicSchool::Nature);
    pchar->get_target()->decrease_magic_school_damage_mod(15, MagicSchool::Shadow);
}
