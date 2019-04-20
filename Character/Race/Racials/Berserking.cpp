#include "Berserking.h"

#include "BerserkingBuff.h"
#include "Character.h"
#include "Race.h"

Berserking::Berserking(Character* pchar) :
    Spell("Berserking", "Assets/races/Racial_troll_berserk.png", pchar, RestrictedByGcd::Yes, 180, ResourceType::Rage, 0),
    buff(new BerserkingBuff(pchar))
{
    this->enabled = false;
}

Berserking::~Berserking() {
    delete buff;
}

void Berserking::spell_effect() {
    buff->apply_buff();

    add_spell_cd_event();
    add_gcd_event();
}

void Berserking::enable_spell_effect() {
    buff->enable_buff();
}

void Berserking::disable_spell_effect() {
    buff->disable_buff();
}
