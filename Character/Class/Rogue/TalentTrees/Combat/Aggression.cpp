#include "Aggression.h"

#include "Eviscerate.h"
#include "SinisterStrike.h"
#include "Rogue.h"
#include "RogueSpells.h"

Aggression::Aggression(Character *pchar, TalentTree* tree) :
    Talent(pchar, tree, "Aggression", "6MR", "Assets/ability/Ability_racial_avatar.png", 3),
    eviscerate(dynamic_cast<RogueSpells*>(dynamic_cast<Rogue*>(pchar)->get_spells())->get_eviscerate()),
    sinister_strike(dynamic_cast<RogueSpells*>(dynamic_cast<Rogue*>(pchar)->get_spells())->get_sinister_strike())
{
    QString base_str = "Increases the damage of your Sinister Strike and Eviscerate abilities by %1%.";
    initialize_rank_descriptions(base_str, 2, 2);
}

void Aggression::apply_rank_effect() {
    eviscerate->increase_talent_rank(eviscerate, name);
    sinister_strike->increase_talent_rank(sinister_strike, name);
}

void Aggression::remove_rank_effect() {
    eviscerate->decrease_talent_rank(eviscerate, name);
    sinister_strike->decrease_talent_rank(sinister_strike, name);
}
