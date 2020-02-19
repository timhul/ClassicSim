#include "RandomAffixModel.h"

#include "EquipmentDb.h"
#include "Item.h"
#include "RandomAffix.h"
#include "RandomAffixes.h"

RandomAffixModel::RandomAffixModel(const int item_id, QObject* parent) :
    QAbstractListModel(parent), equipment_db(nullptr), random_affixes_db(nullptr), item_id(item_id) {}

void RandomAffixModel::set_random_affixes_db(RandomAffixes* random_affixes) {
    this->random_affixes_db = random_affixes;
}

void RandomAffixModel::set_id(const int item_id) {
    this->item_id = item_id;
    update_affixes();
}

void RandomAffixModel::set_equipment_db(EquipmentDb* equipment_db) {
    this->equipment_db = equipment_db;
    update_affixes();
}

void RandomAffixModel::update_affixes() {
    if (!equipment_db || this->item_id < 1)
        return;

    beginResetModel();
    random_affixes.clear();
    random_affixes = equipment_db->get_item(this->item_id)->get_possible_random_affixes();
    endResetModel();
}

int RandomAffixModel::rowCount(const QModelIndex& parent) const {
    Q_UNUSED(parent)
    return random_affixes.count();
}

QVariant RandomAffixModel::data(const QModelIndex& index, int role) const {
    if (!equipment_db || index.row() < 0 || index.row() >= random_affixes.count())
        return QVariant();

    if (role == NameRole)
        return random_affixes_db->get_affix(static_cast<uint>(random_affixes.toList().at(index.row())))->name;
    if (role == DescriptionRole)
        return random_affixes_db->get_affix(static_cast<uint>(random_affixes.toList().at(index.row())))->to_string();
    if (role == IDRole)
        return random_affixes.toList().at(index.row());

    return QVariant();
}

QHash<int, QByteArray> RandomAffixModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[NameRole] = "_name";
    roles[DescriptionRole] = "_descr";
    roles[IDRole] = "_id";
    return roles;
}
