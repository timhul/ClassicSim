
#include "ImprovedExecute.h"
#include "Character.h"

ImprovedExecute::ImprovedExecute(Character *pchar, TalentTree* tree) :
    Talent(pchar, tree, "Improved Execute", "4ML", "Assets/warrior/fury/tier4/Inv_sword_48.png", 2)
{
    QString base_str = "Reduces the rage cost of your Execute abillity by %1.";
    initialize_rank_descriptions(base_str, 2, 3);
}

ImprovedExecute::~ImprovedExecute() {

}

void ImprovedExecute::apply_rank_effect() {
    // TODO: Decide how rank effects work for this talent.
}

void ImprovedExecute::remove_rank_effect() {
    // TODO: Decide how rank effects work for this talent.
}
