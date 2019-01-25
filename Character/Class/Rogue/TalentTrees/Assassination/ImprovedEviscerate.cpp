#include "ImprovedEviscerate.h"

#include "Eviscerate.h"
#include "Rogue.h"
#include "RogueSpells.h"

ImprovedEviscerate::ImprovedEviscerate(Character *pchar, TalentTree* tree) :
    Talent(pchar, tree, "Improved Eviscerate", "1LL", "Assets/ability/Ability_rogue_eviscerate.png", 3),
    eviscerate(dynamic_cast<RogueSpells*>(dynamic_cast<Rogue*>(pchar)->get_spells())->get_eviscerate())
{
    QString base_str = "Increases the damage done by your Eviscerate ability by %1%.";
    initialize_rank_descriptions(rank_descriptions, base_str, max_points, QVector<QPair<int, int>>{{5, 5}});
}

void ImprovedEviscerate::apply_rank_effect() {
    eviscerate->increase_talent_rank(eviscerate, name);
}

void ImprovedEviscerate::remove_rank_effect() {
    eviscerate->decrease_talent_rank(eviscerate, name);
}
