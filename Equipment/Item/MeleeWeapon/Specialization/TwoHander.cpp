
#include "TwoHander.h"

int TwoHander::get_item_slot(void) const {
    return ItemSlots::MAINHAND;
}

int TwoHander::get_weapon_slot() const {
    return WeaponSlots::TWOHAND;
}
