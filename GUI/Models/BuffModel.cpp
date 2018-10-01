
#include "BuffModel.h"
#include "GeneralBuffs.h"
#include "ExternalBuff.h"

BuffModel::BuffModel(GeneralBuffs* general_buffs, QObject *parent)
    : QAbstractListModel(parent),
      general_buffs(general_buffs),
      patch("1.0.0")
{
    addBuffs();
}

void BuffModel::set_patch(const QString &patch) {
    QString patch_split = patch.split(' ').first();
    this->patch = patch_split;
    addBuffs();
}

void BuffModel::addBuffs() {
    if (!external_buffs.empty()) {
        beginRemoveRows(QModelIndex(), 0, external_buffs.size() - 1);
        external_buffs.clear();
        endRemoveRows();
    }

    QVector<ExternalBuff*> buffs = general_buffs->get_external_buffs();
    for (auto buff : buffs) {
        beginInsertRows(QModelIndex(), rowCount(), rowCount());

        if (buff->valid_for_patch(this->patch))
            external_buffs << buff;
        endInsertRows();
    }
}

int BuffModel::rowCount(const QModelIndex & parent) const {
    Q_UNUSED(parent);
    return external_buffs.count();
}

QVariant BuffModel::data(const QModelIndex & index, int role) const {
    if (index.row() < 0 || index.row() >= external_buffs.count())
        return QVariant();

    const ExternalBuff* buff = external_buffs[index.row()];

    if (role == NameRole)
        return buff->get_name();
    if (role == IconRole)
        return buff->get_icon();
    if (role == DescriptionRole)
        return buff->get_description();

    return QVariant();
}

QHash<int, QByteArray> BuffModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[NameRole] = "name";
    roles[IconRole] = "icon";
    roles[DescriptionRole] = "description";
    return roles;
}
