#include "SetBonusRequirer.h"

SetBonusRequirer::SetBonusRequirer(const QSet<QString>& talent_info) :
    set_names(talent_info)
{}

void SetBonusRequirer::activate_set_bonus(const QString& set_name, const int num_pieces) {
    assert(set_names.contains(set_name));
    activate_set_bonus_effect(set_name, num_pieces);
}

void SetBonusRequirer::deactivate_set_bonus(const QString& set_name, const int num_pieces) {
    assert(set_names.contains(set_name));
    deactivate_set_bonus_effect(set_name, num_pieces);
}
