
#include "ImprovedDemoralizingShout.h"
#include "Character.h"

ImprovedDemoralizingShout::ImprovedDemoralizingShout(Character *pchar, TalentTree* tree) :
    Talent(pchar, tree, "Improved Demoralizing Shout", "2ML", "Assets/warrior/fury/tier2/Ability_warrior_warcry.png", 5)
{
    QString base_str = "Increases the melee attack power reduction of your Demoralizing Shout by %1%.";
    initialize_rank_descriptions(base_str, 8, 8);
}

ImprovedDemoralizingShout::~ImprovedDemoralizingShout() {

}

void ImprovedDemoralizingShout::apply_rank_effect() {
    // TODO: Decide how rank effects work for this talent.
}

void ImprovedDemoralizingShout::remove_rank_effect() {
    // TODO: Decide how rank effects work for this talent.
}
