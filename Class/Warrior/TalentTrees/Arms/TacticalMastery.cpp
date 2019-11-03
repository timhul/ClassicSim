#include "TacticalMastery.h"

#include "Warrior.h"

TacticalMastery::TacticalMastery(Warrior* warrior, TalentTree* tree_) :
    Talent(warrior, tree_, "Tactical Mastery", "2ML", "Assets/spell/Spell_nature_enchantarmor.png", 5),
    warrior(warrior)
{
    QString base_str = "You retain up to %1 of your rage points when you change stances.";
    initialize_rank_descriptions(rank_descriptions, base_str, max_points, QVector<QPair<unsigned, unsigned>>{{5, 5}});
}

void TacticalMastery::apply_rank_effect() {
    warrior->increase_stance_rage_remainder();
}

void TacticalMastery::remove_rank_effect() {
    warrior->decrease_stance_rage_remainder();
}
