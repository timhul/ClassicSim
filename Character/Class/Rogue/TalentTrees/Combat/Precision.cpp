#include "Precision.h"

#include "Character.h"
#include "CharacterStats.h"

Precision::Precision(Character *pchar, TalentTree* tree) :
    Talent(pchar, tree, "Precision", "2MR", "Assets/ability/Ability_marksmanship.png", 5)
{
    QString base_str = "Increases your chance to hit with melee weapons by %1%.";
    initialize_rank_descriptions(base_str, 1, 1);
}

Precision::~Precision() = default;

void Precision::apply_rank_effect() {
    pchar->get_stats()->increase_hit(0.01);
}

void Precision::remove_rank_effect() {
    pchar->get_stats()->decrease_hit(0.01);
}
