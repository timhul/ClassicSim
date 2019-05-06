#include "BattleShout.h"

#include "BattleShoutBuff.h"
#include "Warrior.h"

BattleShout::BattleShout(Warrior* pchar) :
    Spell("Battle Shout", "Assets/ability/Ability_warrior_battleshout.png", pchar, RestrictedByGcd::Yes, 0, ResourceType::Rage, 10),
    buff(new BattleShoutBuff(pchar))
{
    buff->enable_buff();
}

BattleShout::~BattleShout() {
    delete buff;
}

Buff* BattleShout::get_buff() const {
    return this->buff;
}

void BattleShout::spell_effect() {
    add_spell_cd_event();
    add_gcd_event();

    buff->apply_buff();

    pchar->lose_rage(resource_cost);
}
