#include "CharacterEnchants.h"

#include "Character.h"
#include "CharacterStats.h"
#include "Equipment.h"
#include "Faction.h"
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

bool CharacterEnchants::has_blunt_weapon(const int equipment_slot) const {
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
    case WeaponTypes::FIST:
    case WeaponTypes::MACE:
    case WeaponTypes::TWOHAND_MACE:
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

bool CharacterEnchants::enchant_valid(EnchantName::Name enchant_name, const int weapon_slot) const {
    switch (weapon_slot) {
    case WeaponSlots::ONEHAND:
    case WeaponSlots::MAINHAND:
    case WeaponSlots::OFFHAND:
        switch (enchant_name) {
        case EnchantName::NoEnchant:
        case EnchantName::Crusader:
        case EnchantName::FieryWeapon:
        case EnchantName::SuperiorStriking:
        case EnchantName::EnchantWeaponAgility:
        case EnchantName::EnchantWeaponStrength:
            return true;
        default:
            return false;
        }
    case WeaponSlots::TWOHAND:
        switch (enchant_name) {
        case EnchantName::NoEnchant:
        case EnchantName::Crusader:
        case EnchantName::FieryWeapon:
        case EnchantName::SuperiorStriking:
        case EnchantName::EnchantWeaponStrength:
        case EnchantName::IronCounterweight:
        case EnchantName::Enchant2HWeaponAgility:
        case EnchantName::Enchant2HWeaponSuperiorImpact:
            return true;
        default:
            return false;
        }
    case WeaponSlots::RANGED:
        switch (enchant_name) {
        case EnchantName::NoEnchant:
        case EnchantName::Biznicks247x128Accurascope:
        case EnchantName::SniperScope:
            return true;
        default:
            return false;
        }

    default:
        return false;
    }
}

bool CharacterEnchants::temp_enchant_valid(EnchantName::Name enchant_name, const int weapon_slot, const int equipment_slot) const {
    switch (weapon_slot) {
    case WeaponSlots::ONEHAND:
    case WeaponSlots::MAINHAND:
    case WeaponSlots::OFFHAND:
    case WeaponSlots::TWOHAND:
        switch (enchant_name) {
        case EnchantName::NoEnchant:
        case EnchantName::ElementalSharpeningStone:
        case EnchantName::ConsecratedSharpeningStone:
            return true;
        case EnchantName::DenseSharpeningStone:
            return has_sharp_weapon(equipment_slot);
        case EnchantName::SolidWeightstone:
            return has_blunt_weapon(equipment_slot);
        case EnchantName::WindfuryTotem:
            return equipment_slot != EquipmentSlot::OFFHAND && pchar->get_faction()->is_horde();
        case EnchantName::InstantPoison:
            return pchar->class_name == "Rogue";
        default:
            return false;
        }
    default:
        return false;
    }
}
