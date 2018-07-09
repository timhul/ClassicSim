
#include "BloodFury.h"
#include "BloodFuryBuff.h"
#include "Race.h"
#include "Warrior.h"

BloodFury::BloodFury(Engine* engine, Character* pchar, CombatRoll* roll) :
    Spell("Blood Fury", engine, pchar, roll, true, 120, 0)
{
    this->pchar = dynamic_cast<Warrior*>(pchar);
}

bool BloodFury::is_ready_spell_specific() const {
    return pchar->get_race()->get_race_int() == Races::Orc;
}

void BloodFury::spell_effect() {
    pchar->get_blood_fury_buff()->apply_buff();

    add_spell_cd_event();
    add_gcd_event();
}
