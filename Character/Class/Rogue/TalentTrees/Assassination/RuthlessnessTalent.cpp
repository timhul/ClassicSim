#include "RuthlessnessTalent.h"

#include "Rogue.h"
#include "Ruthlessness.h"

RuthlessnessTalent::RuthlessnessTalent(Character *pchar, TalentTree* tree) :
    Talent(pchar, tree, "Ruthlessness", "2LL", "Assets/ability/Ability_druid_disembowel.png", 3),
    ruthlessness(dynamic_cast<Rogue*>(pchar)->get_ruthlessness())
{
    QString base_str = "Gives your finishing moves a %1% chance to add a combo point to your target.";
    initialize_rank_descriptions(base_str, 20, 20);
}

void RuthlessnessTalent::apply_rank_effect() {
    ruthlessness->increase_talent_rank(ruthlessness, name);
}

void RuthlessnessTalent::remove_rank_effect() {
    ruthlessness->decrease_talent_rank(ruthlessness, name);
}
