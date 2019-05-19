#include "BloodFury.h"

#include "BloodFuryBuff.h"
#include "CooldownControl.h"
#include "Race.h"
#include "Character.h"

BloodFury::BloodFury(Character* pchar) :
    Spell("Blood Fury", "Assets/races/Racial_orc_berserkerstrength.png", pchar, new CooldownControl(pchar, 120.0), RestrictedByGcd::Yes, ResourceType::Rage, 0),
    buff(new BloodFuryBuff(pchar))
{
    this->enabled = false;
}

BloodFury::~BloodFury() {
    delete buff;
    delete cooldown;
}

void BloodFury::spell_effect() {
    buff->apply_buff();

    cooldown->add_spell_cd_event();
    cooldown->add_gcd_event();
}

void BloodFury::enable_spell_effect() {
    buff->enable_buff();
}

void BloodFury::disable_spell_effect() {
    buff->disable_buff();
}
