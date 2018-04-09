
#include "BattleShout.h"
#include "BattleShoutBuff.h"
#include "Warrior.h"

BattleShout::BattleShout(Engine* engine, Character* pchar, CombatRoll* roll) :
    Spell("Battle Shout", engine, pchar, roll, 0, 10)
{
    this->pchar = dynamic_cast<Warrior*>(pchar);
}

int BattleShout::spell_effect(const int) {
    pchar->get_battle_shout_buff()->apply_buff();

    add_spell_cd_event();
    add_gcd_event();

    return resource_cost;
}
