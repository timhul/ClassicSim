#ifndef DEBUFFMODEL_H
#define DEBUFFMODEL_H

#include <QAbstractListModel>
#include <QStringList>
#include <QVersionNumber>

class Character;
class ExternalBuff;

class DebuffModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum DebuffRoles {
        NameRole = Qt::UserRole + 1,
        IconRole,
        DescriptionRole,
        ActiveRole
    };

    DebuffModel(const QVersionNumber patch, QObject *parent = nullptr);

    void set_character(Character* pchar);
    void set_patch(const QVersionNumber &patch);
    void toggle_debuff(const QString& name);
    void update_debuffs();

    int rowCount(const QModelIndex & parent = QModelIndex()) const;
    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;

private:
    Character* pchar;
    QList<ExternalBuff*> external_debuffs;
    QVersionNumber patch;

    QHash<int, QByteArray> roleNames() const;
};

#endif // DEBUFFMODEL_H
