#include "SetBonusControl.h"

#include "SetBonusFileReader.h"

SetBonusControl::SetBonusControl(EquipmentDb* equipment_db, Character* pchar) :
    equipment_db(equipment_db),
    pchar(pchar)
{
    SetBonusFileReader().read_set_bonuses("set_bonuses.xml", possible_set_items, set_bonus_tooltips);
}

void SetBonusControl::equip_item(const int item_id) {
    if (!possible_set_items.contains(item_id))
        return;

    QString set_name = possible_set_items[item_id];
    current_set_items[item_id] = set_name;
    int num_pieces = get_num_equipped_pieces_for_set(set_name);

    if (set_name == "Bonescythe Armor") {
        switch (num_pieces) {
        case 2:
        case 4:
        case 6:
        case 8:
            break;
        }
    }
}

void SetBonusControl::unequip_item(const int item_id) {
    if (!current_set_items.contains(item_id))
        return;

    QString set_name = current_set_items.take(item_id);
    int num_pieces = get_num_equipped_pieces_for_set(set_name);

    if (set_name == "Bonescythe Armor") {
        switch (num_pieces) {
        case 2:
        case 4:
        case 6:
        case 8:
            break;
        }
    }
}

int SetBonusControl::get_num_equipped_pieces_for_set(const QString& set_name) const {
    int num_set_pieces = 0;
    for (auto & equipped_set : current_set_items) {
        if (equipped_set == set_name)
            ++num_set_pieces;
    }

    return num_set_pieces;
}
