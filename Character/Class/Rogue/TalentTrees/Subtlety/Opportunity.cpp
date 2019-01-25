#include "Opportunity.h"

#include "Backstab.h"
#include "Rogue.h"
#include "RogueSpells.h"

Opportunity::Opportunity(Character* pchar, TalentTree* tree) :
    Talent(pchar, tree, "Opportunity", "1MR", "Assets/ability/Ability_warrior_warcry.png", 5),
    backstab(dynamic_cast<RogueSpells*>(dynamic_cast<Rogue*>(pchar)->get_spells())->get_backstab())
{
    QString base_str = "Increases the damage dealt when striking from behind with your Backstab, Garrote, or Ambush abilities by %1%.";
    initialize_rank_descriptions(rank_descriptions, base_str, max_points, QVector<QPair<int, int>>{{4, 4}});
}

void Opportunity::apply_rank_effect() {
    backstab->increase_talent_rank(backstab, name);
}

void Opportunity::remove_rank_effect() {
    backstab->decrease_talent_rank(backstab, name);
}
