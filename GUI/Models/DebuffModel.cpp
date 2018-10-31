
#include "DebuffModel.h"
#include "GeneralBuffs.h"
#include "ExternalBuff.h"

DebuffModel::DebuffModel(GeneralBuffs* general_debuffs, QObject *parent)
    : QAbstractListModel(parent),
      general_debuffs(general_debuffs),
      patch("1.0.0")
{
    addDebuffs();
}

void DebuffModel::set_patch(const QString &patch) {
    QString patch_split = patch.split(' ').first();
    this->patch = patch_split;
    addDebuffs();
}

void DebuffModel::addDebuffs() {
    if (!external_debuffs.empty()) {
        beginResetModel();
        external_debuffs.clear();
        endResetModel();
    }

    QVector<ExternalBuff*> debuffs = general_debuffs->get_external_debuffs();
    for (auto debuff : debuffs) {
        beginInsertRows(QModelIndex(), rowCount(), rowCount());

        if (debuff->valid_for_patch(this->patch))
            external_debuffs << debuff;
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

    const ExternalBuff* debuff = external_debuffs[index.row()];

    if (role == NameRole)
        return debuff->get_name();
    if (role == IconRole)
        return debuff->get_icon();
    if (role == DescriptionRole)
        return debuff->get_description();

    return QVariant();
}

QHash<int, QByteArray> DebuffModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[NameRole] = "name";
    roles[IconRole] = "icon";
    roles[DescriptionRole] = "description";
    return roles;
}
