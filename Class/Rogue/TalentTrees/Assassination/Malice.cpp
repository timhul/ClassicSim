#include "Malice.h"

#include "Character.h"
#include "CharacterStats.h"

Malice::Malice(Character* pchar, TalentTree* tree) : Talent(pchar, tree, "Malice", "1MR", "Assets/ability/Ability_racial_bloodrage.png", 5) {
    QString base_str = "Increases your critical strike chance by %1%.";
    initialize_rank_descriptions(rank_descriptions, base_str, max_points, QVector<QPair<unsigned, unsigned>> {{1, 1}});
}

Malice::~Malice() = default;

void Malice::apply_rank_effect() {
    pchar->get_stats()->increase_melee_aura_crit(100);
}

void Malice::remove_rank_effect() {
    pchar->get_stats()->decrease_melee_aura_crit(100);
}
