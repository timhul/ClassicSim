#include "PaladinEnchants.h"

#include "Paladin.h"
#include "Utils/Check.h"

PaladinEnchants::PaladinEnchants(Paladin* paladin) : CharacterEnchants(paladin) {}

QVector<EnchantName::Name> PaladinEnchants::get_available_enchants(const int equipment_slot) const {
    switch (equipment_slot) {
    case EquipmentSlot::MAINHAND: {
        QVector<EnchantName::Name> enchants {
            EnchantName::Name::Crusader,
            EnchantName::Name::FieryWeapon,
            EnchantName::Name::EnchantWeaponStrength,
            EnchantName::Name::SuperiorStriking,
            EnchantName::Name::EnchantWeaponSpellPower,
            EnchantName::Name::EnchantWeaponAgility,
        };

        if (has_2hand()) {
            enchants.append({
                EnchantName::Name::Enchant2HWeaponAgility,
                EnchantName::Name::Enchant2HWeaponSuperiorImpact,
                EnchantName::Name::IronCounterweight,
            });
        }

        return enchants;
    }
    case EquipmentSlot::OFFHAND:
    case EquipmentSlot::RANGED:
        return {};
    case EquipmentSlot::HEAD:
    case EquipmentSlot::LEGS:
        return {
            EnchantName::Name::ArcanumOfFocus,
            EnchantName::Name::ArcanumOfRapidity,
            EnchantName::Name::LesserArcanumOfVoracityStrength,
            EnchantName::Name::LesserArcanumOfVoracityAgility,
        };
    case EquipmentSlot::SHOULDERS:
        return {
            EnchantName::Name::ZandalarSignetOfMight,
            EnchantName::Name::ZandalarSignetOfMojo,
            EnchantName::Name::MightOfTheScourge,
            EnchantName::Name::PowerOfTheScourge,
        };
    case EquipmentSlot::BACK:
        return {EnchantName::Name::EnchantCloakLesserAgility};
    case EquipmentSlot::WRIST:
        return {
            EnchantName::Name::EnchantBracerGreaterStrength,
            EnchantName::Name::EnchantBracerSuperiorStrength,
            EnchantName::Name::EnchantBracerGreaterIntellect,
        };
    case EquipmentSlot::GLOVES:
        return {EnchantName::Name::EnchantGlovesSuperiorAgility, EnchantName::Name::EnchantGlovesGreaterAgility,
                EnchantName::Name::EnchantGlovesMinorHaste, EnchantName::Name::EnchantGlovesGreaterStrength};
    case EquipmentSlot::CHEST:
        return {
            EnchantName::Name::EnchantChestMajorMana,
            EnchantName::Name::EnchantChestStats,
            EnchantName::Name::EnchantChestGreaterStats,
        };
    case EquipmentSlot::BOOTS:
        return {
            EnchantName::Name::EnchantBootsMinorSpeed,
            EnchantName::Name::EnchantBootsAgility,
            EnchantName::Name::EnchantBootsGreaterAgility,
            EnchantName::Name::EnchantBootsSpirit,
        };
    }

    check(false, "PaladinEnchants::get_available_enchants reached end of switch");
    return {};
}

QVector<EnchantName::Name> PaladinEnchants::get_available_temp_enchants(const int equipment_slot) const {
    switch (equipment_slot) {
    case EquipmentSlot::MAINHAND: {
        QVector<EnchantName::Name> enchants {
            EnchantName::Name::ElementalSharpeningStone,
            EnchantName::Name::ConsecratedSharpeningStone,
            EnchantName::Name::BrilliantWizardOil,
            EnchantName::Name::ShadowOil,
        };
        if (has_sharp_weapon(equipment_slot))
            enchants.prepend(EnchantName::Name::DenseSharpeningStone);
        else if (has_blunt_weapon(equipment_slot)) {
            enchants.prepend(EnchantName::Name::DenseWeightstone);
            enchants.prepend(EnchantName::Name::SolidWeightstone);
        }
        return enchants;
    }
    case EquipmentSlot::OFFHAND:
        return {};
    }

    check(false, "PaladinEnchants::get_available_temp_enchants reached end of switch");
    return {};
}
