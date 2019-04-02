#include "CharacterEnchants.h"

#include "Character.h"
#include "CharacterStats.h"
#include "Equipment.h"
#include "ItemNamespace.h"
#include "Utils/Check.h"
#include "Weapon.h"

CharacterEnchants::CharacterEnchants(Character* pchar) :
    pchar(pchar)
{}

bool CharacterEnchants::has_sharp_weapon(const int equipment_slot) const {
    Weapon* wpn = nullptr;
    switch (equipment_slot) {
    case EquipmentSlot::MAINHAND:
        wpn = pchar->get_stats()->get_equipment()->get_mainhand();
        break;
    case EquipmentSlot::OFFHAND:
        wpn = pchar->get_stats()->get_equipment()->get_offhand();
        break;
    default:
        check(false, "CharacterEnchants::has_sharp_weapon reached end of switch");
    }

    if (wpn == nullptr)
        return false;

    switch (wpn->get_weapon_type()) {
    case WeaponTypes::AXE:
    case WeaponTypes::TWOHAND_AXE:
    case WeaponTypes::DAGGER:
    case WeaponTypes::POLEARM:
    case WeaponTypes::SWORD:
    case WeaponTypes::TWOHAND_SWORD:
        return true;
    default:
        return false;
    }
}

bool CharacterEnchants::has_2hand() const {
    if (pchar->get_equipment()->get_mainhand() == nullptr)
        return false;

    return pchar->get_equipment()->get_mainhand()->is_2hand();
}
