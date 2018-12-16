#include "ImprovedPoisons.h"

#include "InstantPoison.h"
#include "Rogue.h"

ImprovedPoisons::ImprovedPoisons(Character* pchar, TalentTree* tree) :
    Talent(pchar, tree, "Improved Poisons", "4MR", "Assets/ability/Ability_poisons.png", 5),
    mh_instant_poison(dynamic_cast<Rogue*>(pchar)->get_mh_instant_poison()),
    oh_instant_poison(dynamic_cast<Rogue*>(pchar)->get_oh_instant_poison())
{
    QString base_str = "Increases the chance to apply poisons to your target by %1%.";
    initialize_rank_descriptions(base_str, 2, 2);
}

void ImprovedPoisons::apply_rank_effect() {
    mh_instant_poison->increase_talent_rank(mh_instant_poison, name);
    oh_instant_poison->increase_talent_rank(oh_instant_poison, name);
}

void ImprovedPoisons::remove_rank_effect() {
    mh_instant_poison->decrease_talent_rank(mh_instant_poison, name);
    oh_instant_poison->decrease_talent_rank(oh_instant_poison, name);
}
