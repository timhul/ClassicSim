#include "WarlockEnchants.h"

#include "Utils/Check.h"
#include "Warlock.h"

WarlockEnchants::WarlockEnchants(Warlock* warlock) : CharacterEnchants(warlock) {}

QVector<EnchantName::Name> WarlockEnchants::get_available_enchants(const int equipment_slot) const {
    switch (equipment_slot) {
    case EquipmentSlot::MAINHAND: {
        QVector<EnchantName::Name> enchants {EnchantName::Name::EnchantWeaponSpellPower};

        if (has_2hand()) {
            enchants.append({});
        } else
            enchants.append({});

        return enchants;
    }
    case EquipmentSlot::OFFHAND:
    case EquipmentSlot::RANGED:
        return {};
    case EquipmentSlot::HEAD:
    case EquipmentSlot::LEGS:
        return {
            EnchantName::Name::ArcanumOfFocus,
            EnchantName::Name::HoodooHex,
        };
    case EquipmentSlot::SHOULDERS:
        return {
            EnchantName::Name::ZandalarSignetOfMojo,
            EnchantName::Name::PowerOfTheScourge,
        };
    case EquipmentSlot::BACK:
        return {};
    case EquipmentSlot::WRIST:
        return {
            EnchantName::Name::EnchantBracerManaRegeneration,
            EnchantName::Name::EnchantBracerGreaterIntellect,
        };
    case EquipmentSlot::GLOVES:
        return {
            EnchantName::Name::EnchantGlovesFirePower,
            EnchantName::Name::EnchantGlovesShadowPower,
        };
    case EquipmentSlot::CHEST:
        return {
            EnchantName::Name::EnchantChestMajorMana,
            EnchantName::Name::EnchantChestStats,
            EnchantName::Name::EnchantChestGreaterStats,
        };
    case EquipmentSlot::BOOTS:
        return {
            EnchantName::Name::EnchantBootsMinorSpeed,
            EnchantName::Name::EnchantBootsSpirit,
        };
    }

    check(false, "WarlockEnchants::get_available_enchants reached end of switch");
    return {};
}

QVector<EnchantName::Name> WarlockEnchants::get_available_temp_enchants(const int equipment_slot) const {
    switch (equipment_slot) {
    case EquipmentSlot::MAINHAND: {
        QVector<EnchantName::Name> enchants {
            EnchantName::Name::BrilliantWizardOil,
            EnchantName::Name::ShadowOil,
        };
        return enchants;
    }
    case EquipmentSlot::OFFHAND:
        return {};
    }

    check(false, "WarlockEnchants::get_available_temp_enchants reached end of switch");
    return {};
}
