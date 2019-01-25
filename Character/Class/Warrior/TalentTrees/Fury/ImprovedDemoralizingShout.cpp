
#include "ImprovedDemoralizingShout.h"
#include "Character.h"

ImprovedDemoralizingShout::ImprovedDemoralizingShout(Character *pchar, TalentTree* tree) :
    Talent(pchar, tree, "Improved Demoralizing Shout", "2ML", "Assets/ability/Ability_warrior_warcry.png", 5)
{
    QString base_str = "Increases the melee attack power reduction of your Demoralizing Shout by %1%.";
    initialize_rank_descriptions(rank_descriptions, base_str, max_points, QVector<QPair<int, int>>{{8, 8}});
}

ImprovedDemoralizingShout::~ImprovedDemoralizingShout() = default;

void ImprovedDemoralizingShout::apply_rank_effect() {
    // TODO: Decide how rank effects work for this talent.
}

void ImprovedDemoralizingShout::remove_rank_effect() {
    // TODO: Decide how rank effects work for this talent.
}
