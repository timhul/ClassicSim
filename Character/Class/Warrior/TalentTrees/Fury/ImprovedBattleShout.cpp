
#include "ImprovedBattleShout.h"
#include "BattleShoutBuff.h"
#include "Warrior.h"

ImprovedBattleShout::ImprovedBattleShout(Character *pchar, TalentTree* tree) :
    Talent(pchar, tree, "Improved Battle Shout", "3RR", "Assets/warrior/fury/tier3/Ability_warrior_battleshout.png", 5),
    battle_shout_buff(dynamic_cast<Warrior*>(pchar)->get_battle_shout_buff())
{
    QString base_str = "Increases the melee attack power bonus of your Battle Shout by %1%.";
    initialize_rank_descriptions(base_str, 5, 5);
}

ImprovedBattleShout::~ImprovedBattleShout() = default;

void ImprovedBattleShout::apply_rank_effect() {
    battle_shout_buff->increase_talent_rank(battle_shout_buff, name);
}

void ImprovedBattleShout::remove_rank_effect() {
    battle_shout_buff->decrease_talent_rank(battle_shout_buff, name);
}
