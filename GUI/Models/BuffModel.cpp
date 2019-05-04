#include "BuffModel.h"

#include "Character.h"
#include "EnabledBuffs.h"
#include "ExternalBuff.h"
#include "Faction.h"
#include "GeneralBuffs.h"

BuffModel::BuffModel(const Content::Phase phase, QObject* parent)
    : QAbstractListModel(parent),
      pchar(nullptr),
      phase(phase)
{}

void BuffModel::set_character(Character* pchar) {
    this->last_toggled = -1;
    this->pchar = pchar;
    this->general_buffs = pchar->get_enabled_buffs()->get_general_buffs();
    update_buffs();
}

void BuffModel::set_phase(const Content::Phase phase) {
    this->last_toggled = -1;
    this->phase = phase;
    update_buffs();
}

void BuffModel::toggle_single_buff(const QString& name) {
    QVector<ExternalBuff*> buffs = general_buffs->get_external_buffs();
    for (int i = 0; i < buffs.size(); ++i) {
        if (buffs[i]->get_name() != name)
            continue;

        general_buffs->toggle_external_buff(buffs[i]->get_name());
        last_toggled = i;
        break;
    }

    dataChanged(createIndex(0, 0), createIndex(rowCount(), 0), {ActiveRole});
}

void BuffModel::clear_buffs_and_select_single_buff(const QString& name) {
    QVector<ExternalBuff*> buffs = general_buffs->get_external_buffs();
    for (int i = 0; i < buffs.size(); ++i) {
        if (buffs[i]->get_name() != name) {
            if (general_buffs->buff_active(buffs[i]->get_name()))
                general_buffs->toggle_external_buff(buffs[i]->get_name());

            continue;
        }

        last_toggled = i;

        if (!general_buffs->buff_active(buffs[i]->get_name()))
            general_buffs->toggle_external_buff(buffs[i]->get_name());
    }

    dataChanged(createIndex(0, 0), createIndex(rowCount(), 0), {ActiveRole});
}

void BuffModel::select_range_of_buffs(const QString& name) {
    int target_index = -1;

    QVector<ExternalBuff*> buffs = general_buffs->get_external_buffs();
    for (int i = 0; i < buffs.size(); ++i) {
        if (buffs[i]->get_name() != name)
            continue;

        target_index = i;
        break;
    }

    if (target_index == last_toggled || target_index == -1)
        return;

    if (last_toggled == -1) {
        last_toggled = target_index;
        return;
    }

    if (target_index > last_toggled) {
        for (int i = last_toggled; i <= target_index; ++i) {
            if (!general_buffs->buff_active(buffs[i]->get_name()))
                general_buffs->toggle_external_buff(buffs[i]->get_name());
        }
    }
    else {
        for (int i = last_toggled; i >= target_index; --i) {
            if (!general_buffs->buff_active(buffs[i]->get_name()))
                general_buffs->toggle_external_buff(buffs[i]->get_name());
        }
    }

    last_toggled = target_index;
    dataChanged(createIndex(0, 0), createIndex(rowCount(), 0), {ActiveRole});
}

void BuffModel::update_buffs() {
    if (!external_buffs.empty()) {
        beginResetModel();
        external_buffs.clear();
        endResetModel();
    }

    QVector<ExternalBuff*> buffs = general_buffs->get_external_buffs();
    for (auto buff : buffs) {
        beginInsertRows(QModelIndex(), rowCount(), rowCount());
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
    if (role == ActiveRole)
        return pchar->get_enabled_buffs()->get_general_buffs()->buff_active(buff->get_name());

    return QVariant();
}

QHash<int, QByteArray> BuffModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[NameRole] = "name";
    roles[IconRole] = "icon";
    roles[DescriptionRole] = "description";
    roles[ActiveRole] = "_active";
    return roles;
}
