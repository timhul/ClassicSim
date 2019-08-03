#include "CatFormBuff.h"

#include "CharacterStats.h"
#include "Druid.h"
#include "Equipment.h"

CatFormBuff::CatFormBuff(Druid* pchar):
    SelfBuff(pchar, "Cat Form", "Assets/spell/Spell_nature_ravenform.png",  BuffDuration::PERMANENT, 0)
{}

void CatFormBuff::buff_effect_when_applied() {
    pchar->get_equipment()->druid_cat_form_switch_to_claws();
}

void CatFormBuff::buff_effect_when_removed() {
    pchar->get_equipment()->druid_switch_to_normal_weapon();
}
