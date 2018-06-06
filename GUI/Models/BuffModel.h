#ifndef BUFFMODEL_H
#define BUFFMODEL_H

#include <QAbstractListModel>
#include <QStringList>

class ExternalBuff;
class GeneralBuffs;

class BuffModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum BuffRoles {
        NameRole = Qt::UserRole + 1,
        IconRole,
        DescriptionRole
    };

    BuffModel(GeneralBuffs* general_buffs, QObject *parent = 0);

    void set_patch(const QString &patch);
    void addBuffs();

    int rowCount(const QModelIndex & parent = QModelIndex()) const;
    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;

private:
    QHash<int, QByteArray> roleNames() const;

    GeneralBuffs* general_buffs;
    QList<ExternalBuff*> external_buffs;

    QString patch;
};

#endif // BUFFMODEL_H
