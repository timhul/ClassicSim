
#include "Impale.h"
#include "Character.h"

Impale::Impale(Character *pchar, TalentTree* tree) :
    Talent(pchar, tree, "Impale", "4MR", "Assets/warrior/arms/tier4/Ability_searingarrow.png", 2)
{
    QString base_str = "Increases the critical strike damage bonus of your abilities in Battle, Defensive, and Berserker stance by %1%.";
    initialize_rank_descriptions(base_str, 10, 10);
}

Impale::~Impale() {

}

void Impale::apply_rank_effect() {
    pchar->increase_ability_crit_dmg_mod(0.1);
}

void Impale::remove_rank_effect() {
    pchar->decrease_ability_crit_dmg_mod(0.1);
}
