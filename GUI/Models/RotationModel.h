#pragma once

#include <optional>

#include <QAbstractListModel>
#include <QMap>
#include <QStringList>

class Character;
class Rotation;
class RotationConditionsModel;

class RotationModel : public QAbstractListModel {
    Q_OBJECT
public:
    enum RotationRoles
    {
        NameRole = Qt::UserRole + 1,
        SelectedRole,
        IndexRole,
        DescriptionRole
    };

    RotationModel(QObject* parent = nullptr);
    ~RotationModel();

    void set_character(Character* pchar);
    void addRotations();

    void select_rotation();
    bool set_information_index(const int);

    std::optional<int> get_index_of_rotation_named(QString const& name) const;

    QString get_rotation_information_name() const;
    QString get_rotation_information_description() const;
    RotationConditionsModel* get_rotation_conditions_model() const;

    int rowCount(const QModelIndex& parent = QModelIndex()) const;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;

private:
    Character* pchar;
    int information_index;
    QHash<int, QByteArray> roleNames() const;
    QMap<QString, QVector<Rotation*>> rotations;
    RotationConditionsModel* rotation_conditions_model;

    void clear_rotations();
};
