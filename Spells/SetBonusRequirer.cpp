#include "SetBonusRequirer.h"

#include "Utils/Check.h"

SetBonusRequirer::SetBonusRequirer(QSet<QString> talent_info) : set_names(std::move(talent_info)) {}

void SetBonusRequirer::activate_set_bonus(const QString& set_name, const int num_pieces) {
    check(set_names.contains(set_name), QString("Unknown set '%1'").arg(set_name).toStdString());
    activate_set_bonus_effect(set_name, num_pieces);
}

void SetBonusRequirer::deactivate_set_bonus(const QString& set_name, const int num_pieces) {
    check(set_names.contains(set_name), QString("Unknown set '%1'").arg(set_name).toStdString());
    deactivate_set_bonus_effect(set_name, num_pieces);
}
