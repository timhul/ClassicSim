#include "SealFateTalent.h"

#include "Rogue.h"
#include "SealFate.h"

SealFateTalent::SealFateTalent(Character *pchar, TalentTree* tree) :
    Talent(pchar, tree, "Seal Fate", "6ML", "Assets/spell/Spell_shadow_chilltouch.png", 5),
    seal_fate(dynamic_cast<Rogue*>(pchar)->get_seal_fate())
{
    QString base_str = "Your critical strikes from abilities that add combo points have a %1% chance to add an additional combo point.";
    initialize_rank_descriptions(base_str, 20, 20);
}

void SealFateTalent::apply_rank_effect() {
    seal_fate->increase_talent_rank(seal_fate, name);
}

void SealFateTalent::remove_rank_effect() {
    seal_fate->decrease_talent_rank(seal_fate, name);
}
