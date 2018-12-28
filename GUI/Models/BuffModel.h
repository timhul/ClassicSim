#ifndef BUFFMODEL_H
#define BUFFMODEL_H

#include <QAbstractListModel>
#include <QStringList>
#include <QVersionNumber>

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

    BuffModel(const QVersionNumber patch, QObject *parent = nullptr);

    void set_character(Character* pchar);
    void set_patch(const QVersionNumber &patch);
    void toggle_buff(const QString& name);
    void update_buffs();

    int rowCount(const QModelIndex & parent = QModelIndex()) const;
    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;

private:
    Character* pchar;
    QList<ExternalBuff*> external_buffs;
    QVersionNumber patch;

    QHash<int, QByteArray> roleNames() const;
};

#endif // BUFFMODEL_H
