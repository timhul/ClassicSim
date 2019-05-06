#include "DebuffModel.h"

#include "Character.h"
#include "EnabledBuffs.h"
#include "ExternalBuff.h"
#include "Faction.h"
#include "GeneralBuffs.h"

DebuffModel::DebuffModel(const Content::Phase phase, QObject* parent)
    : QAbstractListModel(parent),
      pchar(nullptr),
      phase(phase)
{}

void DebuffModel::set_character(Character* pchar) {
    this->last_toggled = -1;
    this->pchar = pchar;
    this->general_buffs = pchar->get_enabled_buffs()->get_general_buffs();
    update_debuffs();
}

void DebuffModel::set_phase(const Content::Phase phase) {
    this->last_toggled = -1;
    this->phase = phase;
    update_debuffs();
}

void DebuffModel::toggle_single_debuff(const QString& name) {
    QVector<ExternalBuff*> buffs = pchar->get_enabled_buffs()->get_general_buffs()->get_external_debuffs();
    for (int i = 0; i < buffs.size(); ++i) {
        if (buffs[i]->get_name() != name)
            continue;

        general_buffs->toggle_external_debuff(name);
        last_toggled = i;
        break;
    }

    dataChanged(createIndex(0, 0), createIndex(rowCount(), 0), {ActiveRole});
}

void DebuffModel::clear_debuffs_and_select_single_debuff(const QString& name) {
    QVector<ExternalBuff*> buffs = general_buffs->get_external_debuffs();
    for (int i = 0; i < buffs.size(); ++i) {
        if (buffs[i]->get_name() != name) {
            if (general_buffs->debuff_active(buffs[i]->get_name()))
                general_buffs->toggle_external_debuff(buffs[i]->get_name());

            continue;
        }

        last_toggled = i;

        if (!general_buffs->debuff_active(buffs[i]->get_name()))
            general_buffs->toggle_external_debuff(name);
    }

    dataChanged(createIndex(0, 0), createIndex(rowCount(), 0), {ActiveRole});
}

void DebuffModel::select_range_of_debuffs(const QString& name) {
    int target_index = -1;

    QVector<ExternalBuff*> buffs = general_buffs->get_external_debuffs();
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
            if (!general_buffs->debuff_active(buffs[i]->get_name()))
                general_buffs->toggle_external_debuff(buffs[i]->get_name());
        }
    }
    else {
        for (int i = last_toggled; i >= target_index; --i) {
            if (!general_buffs->debuff_active(buffs[i]->get_name()))
                general_buffs->toggle_external_debuff(buffs[i]->get_name());
        }
    }

    last_toggled = target_index;
    dataChanged(createIndex(0, 0), createIndex(rowCount(), 0), {ActiveRole});
}

void DebuffModel::update_debuffs() {
    if (!external_debuffs.empty()) {
        beginResetModel();
        external_debuffs.clear();
        endResetModel();
    }

    QVector<ExternalBuff*> buffs = pchar->get_enabled_buffs()->get_general_buffs()->get_external_debuffs();
    for (const auto buff : buffs) {
        beginInsertRows(QModelIndex(), rowCount(), rowCount());
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
