
#include "GenericTalent.h"
#include "Character.h"
#include "TalentTree.h"

GenericTalent::GenericTalent(Character *pchar, TalentTree* tree, const QString &name, const QString &position, const QString &icon, const int max_points, const QString &rank_description, const int base_val, const int increment, bool use_increment) :
    Talent(pchar, tree, name, position, icon, max_points)
{
    if (use_increment) {
        initialize_rank_descriptions(rank_description, base_val, increment);
    }
    else {
        rank_descriptions.insert(0, rank_description);
        rank_descriptions.insert(1, rank_description);
    }
}

GenericTalent::~GenericTalent() {

}

void GenericTalent::apply_rank_effect() {}

void GenericTalent::remove_rank_effect() {}
