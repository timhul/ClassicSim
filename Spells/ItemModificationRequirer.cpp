#include "ItemModificationRequirer.h"

ItemModificationRequirer::ItemModificationRequirer(const QSet<int>& items) :
    item_ids(items)
{}

void ItemModificationRequirer::activate_item_modification(const int item_id) {
    assert(item_ids.contains(item_id));
    activate_item_effect(item_id);
}

void ItemModificationRequirer::deactivate_item_modification(const int item_id) {
    assert(item_ids.contains(item_id));
    deactivate_item_effect(item_id);
}
