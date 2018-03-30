
#include "ImprovedSlam.h"
#include "Character.h"

ImprovedSlam::ImprovedSlam(Character *pchar, TalentTree* tree) :
    Talent(pchar, tree, "Improved Slam", "5LL", "Assets/warrior/fury/tier5/Ability_warrior_decisivestrike.png", 5)
{
    QString base_str = "Decreases the casting time of your Slam ability by 0.%1 sec.";
    initialize_rank_descriptions(base_str, 1, 1);
}

ImprovedSlam::~ImprovedSlam() {

}

void ImprovedSlam::apply_rank_effect() {
    // TODO: Decide how rank effects work for this talent.
}

void ImprovedSlam::remove_rank_effect() {
    // TODO: Decide how rank effects work for this talent.
}
