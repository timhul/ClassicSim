
#include "BattleShout.h"
#include "BattleShoutBuff.h"
#include "Warrior.h"

BattleShout::BattleShout(Engine* engine, Character* pchar, CombatRoll* roll) :
    Spell("Battle Shout", engine, pchar, roll, true, 0, 10),
    warr(dynamic_cast<Warrior*>(pchar))
{}

void BattleShout::spell_effect() {
    warr->get_battle_shout_buff()->apply_buff();

    add_spell_cd_event();
    add_gcd_event();

    warr->lose_rage(static_cast<unsigned>(resource_cost));
}
