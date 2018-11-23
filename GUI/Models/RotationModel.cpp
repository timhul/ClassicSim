
#include "RotationModel.h"
#include "Character.h"
#include "Rotation.h"
#include "RotationFileReader.h"

RotationModel::RotationModel(Character *pchar, QObject *parent)
    : QAbstractListModel(parent),
      pchar(pchar),
      patch("1.0.0"),
      information_index(-1)
{}

RotationModel::~RotationModel() {
    for (auto & vectors : rotations.values()) {
        for (auto & i : vectors) {
            delete i;
        }
    }
}

void RotationModel::set_patch(const QString &patch) {
    QString patch_split = patch.split(' ').first();
    this->patch = patch_split;
    addRotations();
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
        for (auto & vectors : rotations.values()) {
            for (auto & i : vectors) {
                delete i;
            }
        }

        rotations.clear();
        endResetModel();
    }

    RotationFileReader rotation_file_reader;
    QVector<Rotation*> new_rotations;
    rotation_file_reader.add_rotations(new_rotations);

    for (auto & rotation : new_rotations) {
        if (rotation == nullptr) {
            delete rotation;
            continue;
        }

        if (!rotations.contains(rotation->get_class()))
            rotations.insert(rotation->get_class(), QVector<Rotation*>({}));

        beginInsertRows(QModelIndex(), rowCount(), rowCount());
        rotations[rotation->get_class()].append(rotation);

        if (rotation->get_class() == pchar->get_name()) {
            if (rotation->get_name() == pchar->get_current_rotation_name())
                information_index = rotations[rotation->get_class()].size() - 1;
        }

        endInsertRows();
    }
}

void RotationModel::select_rotation() {
    if (information_index < 0 || information_index >= rowCount())
        return;

    if (rotations[pchar->get_name()][information_index]->get_name() == pchar->get_current_rotation_name())
        return;

    return pchar->set_rotation(rotations[pchar->get_name()][information_index]);
}

bool RotationModel::set_information_index(const int index) {
    if (index < 0 || index >= rowCount())
        return false;

    layoutAboutToBeChanged();
    information_index = index;
    layoutChanged();
    return true;
}

QString RotationModel::get_rotation_information_name() const {
    if (information_index < 0 || information_index >= rowCount())
        return "";

    return rotations[pchar->get_name()][information_index]->get_name();
}

QString RotationModel::get_rotation_information_description() const {
    if (information_index < 0 || information_index >= rowCount())
        return "";

    return rotations[pchar->get_name()][information_index]->get_description();
}

int RotationModel::rowCount(const QModelIndex & parent) const {
    Q_UNUSED(parent);
    return rotations[pchar->get_name()].size();
}

QVariant RotationModel::data(const QModelIndex & index, int role) const {
    if (index.row() < 0 || index.row() >= rowCount())
        return QVariant();

    const Rotation* rotation = rotations[pchar->get_name()][index.row()];

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
