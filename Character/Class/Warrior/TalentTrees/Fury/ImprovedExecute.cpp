
#include "ImprovedExecute.h"
#include "Execute.h"
#include "Warrior.h"

ImprovedExecute::ImprovedExecute(Character *pchar, TalentTree* tree) :
    Talent(pchar, tree, "Improved Execute", "4ML", "Assets/warrior/fury/tier4/Inv_sword_48.png", 2)
{
    QString base_str = "Reduces the rage cost of your Execute abillity by %1.";
    initialize_rank_descriptions(base_str, 2, 3);
}

ImprovedExecute::~ImprovedExecute() {

}

void ImprovedExecute::apply_rank_effect() {
    dynamic_cast<Warrior*>(pchar)->get_execute()->increase_effect_via_talent();
}

void ImprovedExecute::remove_rank_effect() {
    dynamic_cast<Warrior*>(pchar)->get_execute()->decrease_effect_via_talent();
}
