#ifndef BUFFMODEL_H
#define BUFFMODEL_H

#include <QAbstractListModel>
#include <QStringList>
#include <QVersionNumber>

#include "ContentPhase.h"

class Character;
class ExternalBuff;

class BuffModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum BuffRoles {
        NameRole = Qt::UserRole + 1,
        IconRole,
        DescriptionRole,
        ActiveRole
    };

    BuffModel(const Content::Phase phase, QObject *parent = nullptr);

    void set_character(Character* pchar);
    void set_phase(const Content::Phase phase);
    void toggle_buff(const QString& name);
    void update_buffs();

    int rowCount(const QModelIndex & parent = QModelIndex()) const;
    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;

private:
    Character* pchar;
    QList<ExternalBuff*> external_buffs;
    Content::Phase phase;

    QHash<int, QByteArray> roleNames() const;
};

#endif // BUFFMODEL_H
