#include "ImprovedSinisterStrike.h"

#include "SinisterStrike.h"
#include "Rogue.h"
#include "RogueSpells.h"

ImprovedSinisterStrike::ImprovedSinisterStrike(Character *pchar, TalentTree* tree) :
    Talent(pchar, tree, "Improved Sinister Strike", "1ML", "Assets/spell/Spell_shadow_ritualofsacrifice.png", 2),
    sinister_strike(dynamic_cast<RogueSpells*>(dynamic_cast<Rogue*>(pchar)->get_spells())->get_sinister_strike())
{
    QString base_str = "Reduces the Energy cost of your Sinister Strike ability by %1.";
    initialize_rank_descriptions(base_str, 3, 2);
}

void ImprovedSinisterStrike::apply_rank_effect() {
    sinister_strike->increase_talent_rank(sinister_strike, name);
}

void ImprovedSinisterStrike::remove_rank_effect() {
    sinister_strike->decrease_talent_rank(sinister_strike, name);
}
