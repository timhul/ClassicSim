#ifndef DEBUFFMODEL_H
#define DEBUFFMODEL_H

#include <QAbstractListModel>
#include <QStringList>

class ExternalBuff;
class GeneralBuffs;

class DebuffModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum DebuffRoles {
        NameRole = Qt::UserRole + 1,
        IconRole,
        DescriptionRole
    };

    DebuffModel(GeneralBuffs* general_debuffs, QObject *parent = 0);

    void set_patch(const QString &patch);
    void addDebuffs();

    int rowCount(const QModelIndex & parent = QModelIndex()) const;
    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;

private:
    QHash<int, QByteArray> roleNames() const;

    GeneralBuffs* general_debuffs;
    QList<ExternalBuff*> external_debuffs;

    QString patch;
};

#endif // DEBUFFMODEL_H
