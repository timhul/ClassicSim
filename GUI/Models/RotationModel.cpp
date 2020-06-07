#include "RotationModel.h"

#include <optional>

#include "Character.h"
#include "CharacterSpells.h"
#include "Rotation.h"
#include "RotationConditionsModel.h"
#include "RotationFileReader.h"

RotationModel::RotationModel(QObject* parent) :
    QAbstractListModel(parent), pchar(nullptr), information_index(-1), rotation_conditions_model(new RotationConditionsModel()) {}

RotationModel::~RotationModel() {
    delete rotation_conditions_model;

    clear_rotations();
}

void RotationModel::set_character(Character* pchar) {
    this->pchar = pchar;
    information_index = -1;
    addRotations();

    select_rotation();
}

void RotationModel::addRotations() {
    if (!rotations.empty()) {
        beginResetModel();
        clear_rotations();
        endResetModel();
    }

    QVector<Rotation*> new_rotations;
    RotationFileReader::add_rotations(new_rotations);

    for (const auto& rotation : new_rotations) {
        if (!rotations.contains(rotation->get_class()))
            rotations.insert(rotation->get_class(), QVector<Rotation*>({}));

        beginInsertRows(QModelIndex(), rowCount(), rowCount());
        rotations[rotation->get_class()].append(rotation);

        endInsertRows();
    }
}

void RotationModel::select_rotation() {
    if (information_index < 0 || information_index >= rowCount())
        return;

    pchar->get_spells()->set_rotation(rotations[pchar->class_name][information_index]);
}

bool RotationModel::set_information_index(const int index) {
    if (index < 0 || index >= rowCount())
        return false;

    emit layoutAboutToBeChanged();
    information_index = index;
    rotations[pchar->class_name][information_index]->link_spells(pchar);
    rotation_conditions_model->set_rotation(rotations[pchar->class_name][information_index]);
    emit layoutChanged();
    return true;
}

QString RotationModel::get_rotation_information_name() const {
    if (information_index < 0 || information_index >= rowCount())
        return "";

    return rotations[pchar->class_name][information_index]->get_name();
}

QString RotationModel::get_rotation_information_description() const {
    if (information_index < 0 || information_index >= rowCount())
        return "";

    return rotations[pchar->class_name][information_index]->get_description();
}

RotationConditionsModel* RotationModel::get_rotation_conditions_model() const {
    return this->rotation_conditions_model;
}

int RotationModel::rowCount(const QModelIndex& parent) const {
    Q_UNUSED(parent);
    return rotations[pchar->class_name].size();
}

QVariant RotationModel::data(const QModelIndex& index, int role) const {
    if (index.row() < 0 || index.row() >= rowCount())
        return QVariant();

    const Rotation* rotation = rotations[pchar->class_name][index.row()];

    if (role == NameRole)
        return rotation->get_name();
    if (role == SelectedRole)
        return index.row() == information_index;
    if (role == IndexRole)
        return index.row();
    if (role == DescriptionRole)
        return rotation->get_description();

    return QVariant();
}

QHash<int, QByteArray> RotationModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[NameRole] = "_name";
    roles[SelectedRole] = "_selected";
    roles[IndexRole] = "_index";
    roles[DescriptionRole] = "_description";

    return roles;
}

void RotationModel::clear_rotations() {
    for (const auto& class_rotations : rotations)
        for (const auto& rotation : class_rotations)
            delete rotation;

    rotations.clear();
}

std::optional<int> RotationModel::get_index_of_rotation_named(QString const& name) const {
    for (int i = 0; i < rotations[pchar->class_name].size(); ++i) {
        if (rotations[pchar->class_name][i]->get_name() == name)
            return i;
    }

    return std::nullopt;
}
