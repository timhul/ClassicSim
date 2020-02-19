#pragma once

#include <QAbstractListModel>
#include <QStringList>
#include <QVersionNumber>

#include "ContentPhase.h"

class Character;
class ExternalBuff;
class GeneralBuffs;

class DebuffModel : public QAbstractListModel {
    Q_OBJECT
public:
    enum DebuffRoles
    {
        NameRole = Qt::UserRole + 1,
        IconRole,
        DescriptionRole,
        ActiveRole
    };

    DebuffModel(const Content::Phase phase, QObject* parent = nullptr);

    void set_character(Character* pchar);
    void set_phase(const Content::Phase phase);
    void toggle_single_debuff(const QString& name);
    void clear_debuffs_and_select_single_debuff(const QString& name);
    void select_range_of_debuffs(const QString& name);
    void update_debuffs();

    int rowCount(const QModelIndex& parent = QModelIndex()) const;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;

private:
    Character* pchar;
    GeneralBuffs* general_buffs {nullptr};
    QList<ExternalBuff*> external_debuffs;
    Content::Phase phase;
    int last_toggled {-1};

    QHash<int, QByteArray> roleNames() const;
};
