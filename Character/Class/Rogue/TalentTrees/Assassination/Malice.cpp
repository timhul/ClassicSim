#include "Malice.h"

#include "Character.h"
#include "CharacterStats.h"

Malice::Malice(Character *pchar, TalentTree* tree) :
    Talent(pchar, tree, "Malice", "1MR", "Assets/ability/Ability_racial_bloodrage.png", 5)
{
    QString base_str = "Increases your critical strike chance by %1%.";
    initialize_rank_descriptions(base_str, 1, 1);
}

Malice::~Malice() = default;

void Malice::apply_rank_effect() {
    pchar->get_stats()->increase_crit(0.01);
}

void Malice::remove_rank_effect() {
    pchar->get_stats()->decrease_crit(0.01);
}
