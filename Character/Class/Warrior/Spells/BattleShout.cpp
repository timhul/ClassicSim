#include "BattleShout.h"

#include "BattleShoutBuff.h"
#include "Warrior.h"
#include "WarriorSpells.h"

BattleShout::BattleShout(Warrior* pchar, WarriorSpells* spells) :
    Spell("Battle Shout", "Assets/ability/Ability_warrior_battleshout.png", pchar, RestrictedByGcd::Yes, 0, ResourceType::Rage, 10),
    warr(pchar),
    spells(spells)
{}

void BattleShout::spell_effect() {
    spells->get_battle_shout_buff()->apply_buff();

    add_spell_cd_event();
    add_gcd_event();

    warr->lose_rage(resource_cost);
}
