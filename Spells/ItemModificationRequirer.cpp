#include "ItemModificationRequirer.h"

#include "Utils/Check.h"

ItemModificationRequirer::ItemModificationRequirer(QSet<int> items) :
    item_ids(std::move(items))
{}

void ItemModificationRequirer::activate_item_modification(const int item_id) {
    check(item_ids.contains(item_id), QString("Unknown item id '%1").arg(item_id).toStdString());
    activate_item_effect(item_id);
}

void ItemModificationRequirer::deactivate_item_modification(const int item_id) {
    check(item_ids.contains(item_id), QString("Unknown item id '%1").arg(item_id).toStdString());
    deactivate_item_effect(item_id);
}
