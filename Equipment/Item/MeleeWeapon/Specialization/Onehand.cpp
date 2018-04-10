
#include "Onehand.h"

int Onehand::get_item_type(void) const {
    return ItemSlots::MAINHAND;
}

int Onehand::get_weapon_slot() const {
    return WeaponSlots::ONEHAND;
}
