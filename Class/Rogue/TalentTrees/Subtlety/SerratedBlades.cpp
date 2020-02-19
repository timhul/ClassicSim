#include "SerratedBlades.h"

#include "Character.h"
#include "Target.h"

SerratedBlades::SerratedBlades(Character* pchar, TalentTree* tree) :
    Talent(pchar, tree, "Serrated Blades", "4MR", "Assets/items/Inv_sword_17.png", 3) {
    QString base_str = "Causes your attacks to ignore %1 of your target's Armor and increases the damage dealt by your Rupture ability by %2%. The "
                       "amount of Armor reduced increases with your level.";
    initialize_rank_descriptions(rank_descriptions, base_str, max_points, QVector<QPair<unsigned, unsigned>> {{100, 100}, {10, 10}});
}

void SerratedBlades::apply_rank_effect() {
    pchar->get_target()->decrease_armor(100);
}

void SerratedBlades::remove_rank_effect() {
    pchar->get_target()->increase_armor(100);
}
