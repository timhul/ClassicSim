#include "BattleShout.h"

#include "BattleShoutBuff.h"
#include "CooldownControl.h"
#include "EnabledBuffs.h"
#include "Warrior.h"

BattleShout::BattleShout(Warrior* pchar, BattleShoutBuff* buff) :
    Spell("Battle Shout", "Assets/ability/Ability_warrior_battleshout.png", pchar, new CooldownControl(pchar, 0.0), RestrictedByGcd::Yes, ResourceType::Rage, 10),
    buff(buff)
{
    buff->enable_buff();
}

BattleShout::~BattleShout() {
    delete cooldown;
}

Buff* BattleShout::get_buff() const {
    return this->buff;
}

void BattleShout::spell_effect() {
    cooldown->add_spell_cd_event();
    cooldown->add_gcd_event();

    buff->apply_buff();

    pchar->lose_rage(resource_cost);
}
