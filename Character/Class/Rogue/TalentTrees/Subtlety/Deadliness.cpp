#include "Deadliness.h"

#include "Character.h"
#include "CharacterStats.h"

Deadliness::Deadliness(Character* pchar, TalentTree* tree) :
    Talent(pchar, tree, "Deadliness", "6MR", "Assets/items/Inv_weapon_crossbow_11.png", 5)
{
    QString base_str = "Increases your Attack Power by %1%.";
    initialize_rank_descriptions(rank_descriptions, base_str, max_points, QVector<QPair<int, int>>{{2, 2}});

    this->ap_multipliers = {0, 2, 4, 6, 8, 10};
}

void Deadliness::apply_rank_effect() {
    if (curr_points != 1)
        pchar->get_stats()->remove_ap_multiplier(ap_multipliers[curr_points - 1]);

    pchar->get_stats()->add_ap_multiplier(ap_multipliers[curr_points]);
}

void Deadliness::remove_rank_effect() {
    pchar->get_stats()->remove_ap_multiplier(ap_multipliers[curr_points + 1]);

    if (curr_points != 0)
        pchar->get_stats()->add_ap_multiplier(ap_multipliers[curr_points]);
}
