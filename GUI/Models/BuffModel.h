#pragma once

#include <QAbstractListModel>
#include <QStringList>
#include <QVersionNumber>

#include "ContentPhase.h"

class Character;
class ExternalBuff;
class GeneralBuffs;

class BuffModel : public QAbstractListModel {
    Q_OBJECT
public:
    enum BuffRoles
    {
        NameRole = Qt::UserRole + 1,
        IconRole,
        DescriptionRole,
        ActiveRole
    };

    BuffModel(const Content::Phase phase, QObject* parent = nullptr);

    void set_character(Character* pchar);
    void set_phase(const Content::Phase phase);
    void toggle_single_buff(const QString& name);
    void clear_buffs_and_select_single_buff(const QString& name);
    void select_range_of_buffs(const QString& name);
    void update_buffs();

    int rowCount(const QModelIndex& parent = QModelIndex()) const;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;

private:
    Character* pchar;
    GeneralBuffs* general_buffs {nullptr};
    QList<ExternalBuff*> external_buffs;
    Content::Phase phase;
    int last_toggled {-1};

    QHash<int, QByteArray> roleNames() const;
};
