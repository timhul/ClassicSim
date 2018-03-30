
#include "Cruelty.h"
#include "Character.h"

Cruelty::Cruelty(Character *pchar, TalentTree* tree) :
    Talent(pchar, tree, "Cruelty", "1MR", "Assets/warrior/fury/tier1/Ability_rogue_eviscerate.png", 5)
{
    QString base_str = "Increases your chance to get a critical strike with melee weapons by %1%.";
    initialize_rank_descriptions(base_str, 1, 1);
}

Cruelty::~Cruelty() {

}

void Cruelty::apply_rank_effect() {
    pchar->increase_crit(1.0);
}

void Cruelty::remove_rank_effect() {
    pchar->decrease_crit(1.0);
}
