
#include "ImprovedBattleShout.h"
#include "Character.h"

ImprovedBattleShout::ImprovedBattleShout(Character *pchar, TalentTree* tree) :
    Talent(pchar, tree, "Improved Battle Shout", "3RR", "Assets/warrior/fury/tier3/Ability_warrior_battleshout.png", 5)
{
    QString base_str = "Increases the melee attack power bonus of your Battle Shout by %1%.";
    initialize_rank_descriptions(base_str, 5, 5);
}

ImprovedBattleShout::~ImprovedBattleShout() {

}

void ImprovedBattleShout::apply_rank_effect() {
    // TODO: Decide how rank effects work for this talent.
}

void ImprovedBattleShout::remove_rank_effect() {
    // TODO: Decide how rank effects work for this talent.
}
