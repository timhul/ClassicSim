#include "Cruelty.h"

#include "Character.h"
#include "CharacterStats.h"

Cruelty::Cruelty(Character *pchar, TalentTree* tree) :
    Talent(pchar, tree, "Cruelty", "1MR", "Assets/ability/Ability_rogue_eviscerate.png", 5)
{
    QString base_str = "Increases your chance to get a critical strike with melee weapons by %1%.";
    initialize_rank_descriptions(rank_descriptions, base_str, max_points, QVector<QPair<unsigned, unsigned>>{{1, 1}});
}

Cruelty::~Cruelty() = default;

void Cruelty::apply_rank_effect() {
    pchar->get_stats()->increase_melee_crit(100);
}

void Cruelty::remove_rank_effect() {
    pchar->get_stats()->decrease_melee_crit(100);
}
