#include "StormstrikeBuff.h"

#include "Character.h"
#include "Target.h"

StormstrikeBuff::StormstrikeBuff(Character* pchar):
    SharedDebuff(pchar, "Stormstrike", "Assets/spell/Spell_holy_sealofmight.png", 12, 2)
{}

void StormstrikeBuff::buff_effect_when_applied() {
    pchar->get_target()->increase_magic_school_damage_mod(20, MagicSchool::Nature);
    pchar->get_target()->add_charge_debuff(this, ConsumedWhen::OnSpellDamageMod, MagicSchool::Nature);
}

void StormstrikeBuff::buff_effect_when_removed() {
    pchar->get_target()->decrease_magic_school_damage_mod(20, MagicSchool::Nature);
    pchar->get_target()->remove_charge_debuff(this, ConsumedWhen::OnSpellDamageMod, MagicSchool::Nature);
}
