#include "Lethality.h"

#include "Backstab.h"
#include "Hemorrhage.h"
#include "Rogue.h"
#include "RogueSpells.h"
#include "SinisterStrike.h"

Lethality::Lethality(Character *pchar, TalentTree* tree) :
    Talent(pchar, tree, "Lethality", "3MR", "Assets/ability/Ability_criticalstrike.png", 5),
    backstab(dynamic_cast<RogueSpells*>(dynamic_cast<Rogue*>(pchar)->get_spells())->get_backstab()),
    hemorrhage(dynamic_cast<RogueSpells*>(dynamic_cast<Rogue*>(pchar)->get_spells())->get_hemorrhage()),
    sinister_strike(dynamic_cast<RogueSpells*>(dynamic_cast<Rogue*>(pchar)->get_spells())->get_sinister_strike())
{
    QString base_str = "Increases the critical strike damage bonus of your Sinister Strike, Gouge, Backstab, Ghostly Strike, and Hemorrhage abilities by %1%.";
    initialize_rank_descriptions(base_str, 6, 6);
}

void Lethality::apply_rank_effect() {
    backstab->increase_talent_rank(backstab, name);
    hemorrhage->increase_talent_rank(hemorrhage, name);
    sinister_strike->increase_talent_rank(sinister_strike, name);
}

void Lethality::remove_rank_effect() {
    backstab->decrease_talent_rank(backstab, name);
    hemorrhage->decrease_talent_rank(hemorrhage, name);
    sinister_strike->decrease_talent_rank(sinister_strike, name);
}
