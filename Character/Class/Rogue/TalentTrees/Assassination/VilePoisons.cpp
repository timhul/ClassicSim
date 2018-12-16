#include "VilePoisons.h"

#include "InstantPoison.h"
#include "Rogue.h"

VilePoisons::VilePoisons(Character* pchar, TalentTree* tree) :
    Talent(pchar, tree, "Vile Poisons", "4ML", "Assets/ability/Ability_rogue_feigndeath.png", 5),
    mh_instant_poison(dynamic_cast<Rogue*>(pchar)->get_mh_instant_poison()),
    oh_instant_poison(dynamic_cast<Rogue*>(pchar)->get_oh_instant_poison())
{
    QString base_str = "Increases the damage dealt by your poisons by %1% and gives your poisons an additional %2% chance to resist dispel effects.";
    initialize_rank_descriptions(base_str, QVector<QPair<int, int>>{QPair<int, int>(4, 4), QPair<int, int>(8, 8)});
}

void VilePoisons::apply_rank_effect() {
    mh_instant_poison->increase_talent_rank(mh_instant_poison, name);
    oh_instant_poison->increase_talent_rank(oh_instant_poison, name);
}

void VilePoisons::remove_rank_effect() {
    mh_instant_poison->decrease_talent_rank(mh_instant_poison, name);
    oh_instant_poison->decrease_talent_rank(oh_instant_poison, name);
}
