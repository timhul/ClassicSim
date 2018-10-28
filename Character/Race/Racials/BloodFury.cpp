
#include "BloodFury.h"
#include "BloodFuryBuff.h"
#include "Race.h"
#include "Character.h"

BloodFury::BloodFury(Character* pchar) :
    Spell("Blood Fury", "Assets/Racial_orc_berserkerstrength.png", pchar, true, 120, 0),
    buff(new BloodFuryBuff(pchar))
{
    this->enabled = false;
}

BloodFury::~BloodFury() {
    delete buff;
}

void BloodFury::spell_effect() {
    buff->apply_buff();

    add_spell_cd_event();
    add_gcd_event();
}

void BloodFury::enable_spell_effect() {
    buff->enable_buff();
}

void BloodFury::disable_spell_effect() {
    buff->disable_buff();
}
