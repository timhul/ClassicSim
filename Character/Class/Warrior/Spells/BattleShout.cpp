
#include "BattleShout.h"
#include "BattleShoutBuff.h"
#include "Warrior.h"

BattleShout::BattleShout(Character* pchar) :
    Spell("Battle Shout", "Assets/warrior/fury/tier3/Ability_warrior_battleshout.png", pchar, RestrictedByGcd::Yes, 0, Resource::Rage, 10),
    warr(dynamic_cast<Warrior*>(pchar))
{}

void BattleShout::spell_effect() {
    warr->get_battle_shout_buff()->apply_buff();

    add_spell_cd_event();
    add_gcd_event();

    warr->lose_rage(static_cast<unsigned>(resource_cost));
}
