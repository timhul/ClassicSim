#include "DruidEnchants.h"

#include "Druid.h"
#include "Faction.h"
#include "Utils/Check.h"

DruidEnchants::DruidEnchants(Druid* Druid) : CharacterEnchants(Druid) {}

QVector<EnchantName::Name> DruidEnchants::get_available_enchants(const int equipment_slot) const {
    switch (equipment_slot) {
    case EquipmentSlot::MAINHAND: {
        QVector<EnchantName::Name> enchants {
            EnchantName::Name::EnchantWeaponStrength,
            EnchantName::Name::EnchantWeaponSpellPower,
            EnchantName::Name::EnchantWeaponAgility,
        };

        if (has_2hand()) {
            enchants.append({
                EnchantName::Name::Enchant2HWeaponAgility,
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
            EnchantName::Name::ArcanumOfRapidity,
            EnchantName::Name::LesserArcanumOfVoracityAgility,
            EnchantName::Name::ArcanumOfFocus,
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
            EnchantName::Name::EnchantBracerManaRegeneration, EnchantName::Name::EnchantBracerGreaterStrength,
            EnchantName::Name::EnchantBracerSuperiorStrength, EnchantName::Name::EnchantBracerMinorAgility,
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

    check(false, "DruidEnchants::get_available_enchants reached end of switch");
    return {};
}

QVector<EnchantName::Name> DruidEnchants::get_available_temp_enchants(const int equipment_slot) const {
    switch (equipment_slot) {
    case EquipmentSlot::MAINHAND: {
        QVector<EnchantName::Name> enchants {
            EnchantName::Name::ElementalSharpeningStone, EnchantName::Name::ConsecratedSharpeningStone, EnchantName::Name::LesserManaOil,
            EnchantName::Name::BrilliantManaOil,         EnchantName::Name::BrilliantWizardOil,
        };

        return enchants;
    }
    case EquipmentSlot::OFFHAND:
        QVector<EnchantName::Name> enchants {
            EnchantName::Name::ConsecratedSharpeningStone, EnchantName::Name::ElementalSharpeningStone, EnchantName::Name::LesserManaOil,
            EnchantName::Name::BrilliantManaOil,           EnchantName::Name::BrilliantWizardOil,
        };

        return enchants;
    }

    check(false, "DruidEnchants::get_available_temp_enchants reached end of switch");
    return {};
}
