
#include "GenericTalent.h"
#include "Character.h"

GenericTalent::GenericTalent(Character *pchar, const QString &name, const QString &position, const QString &icon, const int max_points, const QString &req_string_parent_, const QString &req_string_base_, const QString &rank_description, const int base_val, const int increment, bool use_increment) :
    Talent(pchar, name, position, icon, max_points),
    req_string_parent(req_string_parent_),
    req_string_base(req_string_base_)
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

QString GenericTalent::get_requirement_string() const {
    QString req_string = "";
    if (parent != nullptr && !parent->is_maxed()) {
        req_string = req_string_parent;
    }

    return req_string + req_string_base;
}
