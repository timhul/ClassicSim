
#include "RotationModel.h"
#include "Character.h"
#include "Rotation.h"
#include "RotationFileReader.h"

RotationModel::RotationModel(Character *pchar, QObject *parent)
    : QAbstractListModel(parent),
      pchar(pchar),
      patch("1.0.0")
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
    addRotations();
}

void RotationModel::addRotations() {
    if (!rotations.empty()) {
        beginRemoveRows(QModelIndex(), 0, rotations.size() - 1);
        rotations.clear();
        endRemoveRows();
    }

    RotationFileReader rotation_file_reader;
    Rotation* rotation = rotation_file_reader.get_rotation("rotation_arms.xml");

    if (rotation == nullptr)
        return;

    if (!rotations.contains(rotation->get_class()))
        rotations.insert(rotation->get_class(), QVector<Rotation*>({}));

    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    rotations[rotation->get_class()].append(rotation);
    endInsertRows();
}

bool RotationModel::select_rotation(const int index) {
    if (index < 0 || index >= rotations[pchar->get_name()].size())
        return false;

    return pchar->set_rotation(rotations[pchar->get_name()][index]);
}

int RotationModel::rowCount(const QModelIndex & parent) const {
    Q_UNUSED(parent);
    return rotations[pchar->get_name()].size();
}

QVariant RotationModel::data(const QModelIndex & index, int role) const {
    if (index.row() < 0 || index.row() >= rotations.count())
        return QVariant();

    const Rotation* rotation = rotations[pchar->get_name()][index.row()];

    if (role == NameRole)
        return rotation->get_name();
    if (role == IndexRole)
        return index.row();
    if (role == SelectedRole)
        return rotations[pchar->get_name()][index.row()]->get_name() == pchar->get_current_rotation_name();
    if (role == DescriptionRole)
        return rotation->get_description();

    return QVariant();
}

QHash<int, QByteArray> RotationModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[NameRole] = "_name";
    roles[IndexRole] = "_index";
    roles[IndexRole] = "_selected";
    roles[DescriptionRole] = "_description";
    return roles;
}
