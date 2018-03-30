
#include "ImprovedOverpower.h"
#include <QDebug>

ImprovedOverpower::ImprovedOverpower(Character *pchar, TalentTree* tree) :
    Talent(pchar, tree, "Improved Overpower", "3LL", "Assets/warrior/arms/tier3/Inv_sword_05.png", 2)
{
    QString base_str = "Increase the critical strike chance of your Overpower ability by %1%.";
    initialize_rank_descriptions(base_str, 25, 25);
}

ImprovedOverpower::~ImprovedOverpower() {

}

void ImprovedOverpower::apply_rank_effect() {
    // TODO: Decide how rank effects work for this talent.
}

void ImprovedOverpower::remove_rank_effect() {
    // TODO: Decide how rank effects work for this talent.
}
