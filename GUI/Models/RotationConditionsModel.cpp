#include "RotationConditionsModel.h"

#include "Rotation.h"
#include "RotationExecutor.h"
#include "RotationFileReader.h"
#include "Spell.h"
#include <QDebug>
RotationConditionsModel::RotationConditionsModel(QObject *parent)
    : QAbstractListModel(parent)
{}

void RotationConditionsModel::set_rotation(Rotation* rotation) {
    beginResetModel();
    this->rotation = rotation;
    endResetModel();
}

int RotationConditionsModel::rowCount(const QModelIndex & parent) const {
    Q_UNUSED(parent);
    if (!rotation)
        return 0;

    return rotation->all_executors.size();
}

QVariant RotationConditionsModel::data(const QModelIndex & index, int role) const {
    if (index.row() < 0 || index.row() >= rowCount())
        return QVariant();

    const RotationExecutor* executor = rotation->all_executors[index.row()];

    if (role == NameRole) {
        QString spell_rank = "";
        if (executor->get_spell_rank() != Spell::MAX_RANK)
            spell_rank = QString("R%1 ").arg(executor->get_spell_rank());

        return QString("%1%2").arg(spell_rank).arg(executor->get_spell_name());
    }
    if (role == IconRole)
        return executor->get_spell() != nullptr ? executor->get_spell()->get_icon() : "Assets/cross.png";
    if (role == ConditionsRole)
        return executor->get_conditions_string();

    return QVariant();
}

QHash<int, QByteArray> RotationConditionsModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[NameRole] = "_name";
    roles[IconRole] = "_icon";
    roles[ConditionsRole] = "_conditions";

    return roles;
}
