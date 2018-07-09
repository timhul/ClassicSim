
#include "BloodFury.h"
#include "BloodFuryBuff.h"
#include "Race.h"
#include "Character.h"

BloodFury::BloodFury(Engine* engine, Character* pchar, CombatRoll* roll) :
    Spell("Blood Fury", engine, pchar, roll, true, 120, 0)
{
    this->is_enabled_externally = true;
    this->enabled = false;
}

void BloodFury::spell_effect() {
    pchar->get_blood_fury_buff()->apply_buff();

    add_spell_cd_event();
    add_gcd_event();
}

void BloodFury::enable_spell_effect() {
    pchar->get_blood_fury_buff()->enable_buff();
}

void BloodFury::disable_spell_effect() {
    pchar->get_blood_fury_buff()->disable_buff();
}
