#include "RelentlessStrikesTalent.h"

#include "Rogue.h"
#include "RelentlessStrikes.h"

RelentlessStrikesTalent::RelentlessStrikesTalent(Character *pchar, TalentTree* tree) :
    Talent(pchar, tree, "Relentless Strikes", "3LL", "Assets/ability/Ability_warrior_decisivestrike.png", 1),
    RelentlessStrikes(dynamic_cast<Rogue*>(pchar)->get_relentless_strikes())
{
    QString base_str = "Your finishing moves have a 20% chance per combo point to restore 25 Energy.";
    rank_descriptions.insert(0, base_str);
    rank_descriptions.insert(1, base_str);
}

void RelentlessStrikesTalent::apply_rank_effect() {
    RelentlessStrikes->increase_talent_rank(RelentlessStrikes, name);
}

void RelentlessStrikesTalent::remove_rank_effect() {
    RelentlessStrikes->decrease_talent_rank(RelentlessStrikes, name);
}
