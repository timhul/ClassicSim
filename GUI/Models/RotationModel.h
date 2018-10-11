#ifndef ROTATIONMODEL_H
#define ROTATIONMODEL_H

#include <QAbstractListModel>
#include <QStringList>
#include <QMap>

class Character;
class Rotation;

class RotationModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum RotationRoles {
        NameRole = Qt::UserRole + 1,
        IndexRole,
        SelectedRole,
        DescriptionRole
    };

    RotationModel(Character* pchar, QObject *parent = nullptr);
    ~RotationModel();

    void set_patch(const QString &patch);
    void set_character(Character* pchar);
    void addRotations();

    bool select_rotation(const int);

    int rowCount(const QModelIndex & parent = QModelIndex()) const;
    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;

private:
    Character* pchar;
    QString patch;
    QHash<int, QByteArray> roleNames() const;
    QMap<QString, QVector<Rotation*>> rotations;
};

#endif // ROTATIONMODEL_H
