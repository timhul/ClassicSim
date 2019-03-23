#include "DebuffModel.h"

#include "Character.h"
#include "EnabledBuffs.h"
#include "ExternalBuff.h"
#include "Faction.h"
#include "GeneralBuffs.h"

DebuffModel::DebuffModel(const QVersionNumber& patch, QObject* parent)
    : QAbstractListModel(parent),
      pchar(nullptr),
      patch(patch)
{}

void DebuffModel::set_character(Character* pchar) {
    this->pchar = pchar;
    update_debuffs();
}

void DebuffModel::set_patch(const QVersionNumber &patch) {
    this->patch = patch;
    update_debuffs();
}

void DebuffModel::toggle_debuff(const QString& name) {
    QVector<ExternalBuff*> buffs = pchar->get_enabled_buffs()->get_general_buffs()->get_external_debuffs();
    for (int i = 0; i < buffs.size(); ++i) {
        if (buffs[i]->get_name() != name)
            continue;

        pchar->get_enabled_buffs()->get_general_buffs()->toggle_external_debuff(name);

        dataChanged(createIndex(i, 0), createIndex(i, 0), {ActiveRole});
        break;
    }
}

void DebuffModel::update_debuffs() {
    if (!external_debuffs.empty()) {
        beginResetModel();
        external_debuffs.clear();
        endResetModel();
    }

    QVector<ExternalBuff*> buffs = pchar->get_enabled_buffs()->get_general_buffs()->get_external_debuffs();
    for (auto buff : buffs) {
        beginInsertRows(QModelIndex(), rowCount(), rowCount());

        if (buff->valid_for_patch(this->patch.toString()))
            external_debuffs << buff;
        endInsertRows();
    }
}

int DebuffModel::rowCount(const QModelIndex & parent) const {
    Q_UNUSED(parent);
    return external_debuffs.count();
}

QVariant DebuffModel::data(const QModelIndex & index, int role) const {
    if (index.row() < 0 || index.row() >= external_debuffs.count())
        return QVariant();

    const ExternalBuff* buff = external_debuffs[index.row()];

    if (role == NameRole)
        return buff->get_name();
    if (role == IconRole)
        return buff->get_icon();
    if (role == DescriptionRole)
        return buff->get_description();
    if (role == ActiveRole)
        return pchar->get_enabled_buffs()->get_general_buffs()->debuff_active(buff->get_name());

    return QVariant();
}

QHash<int, QByteArray> DebuffModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[NameRole] = "name";
    roles[IconRole] = "icon";
    roles[DescriptionRole] = "description";
    roles[ActiveRole] = "_active";
    return roles;
}
