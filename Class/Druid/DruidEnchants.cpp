#include "DruidEnchants.h"

#include "Faction.h"
#include "Druid.h"
#include "Utils/Check.h"

DruidEnchants::DruidEnchants(Druid* Druid) :
    CharacterEnchants(Druid)
{}

QVector<EnchantName::Name> DruidEnchants::get_available_enchants(const int equipment_slot) const {
    switch (equipment_slot) {
    case EquipmentSlot::MAINHAND: {
        QVector<EnchantName::Name> enchants {
            EnchantName::Name::EnchantWeaponStrength,
            EnchantName::Name::EnchantWeaponSpellPower,
        };

        if (has_2hand()) {
            enchants.append({
                                EnchantName::Name::Enchant2HWeaponAgility,
                                EnchantName::Name::IronCounterweight,
                            });
        }
        else
           enchants.append(EnchantName::Name::EnchantWeaponAgility);

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
            EnchantName::Name::MightOfTheScourge,
            EnchantName::Name::ZandalarSignetOfMight,
            EnchantName::Name::ZandalarSignetOfMojo,
        };
    case EquipmentSlot::BACK:
        return {
            EnchantName::Name::EnchantCloakLesserAgility
        };
    case EquipmentSlot::WRIST:
        return {
            EnchantName::Name::EnchantBracerManaRegeneration,
            EnchantName::Name::EnchantBracerSuperiorStrength,
            EnchantName::Name::EnchantBracerMinorAgility,
        };
    case EquipmentSlot::GLOVES:
        return {
            EnchantName::Name::EnchantGlovesSuperiorAgility,
            EnchantName::Name::EnchantGlovesGreaterAgility,
            EnchantName::Name::EnchantGlovesMinorHaste,
            EnchantName::Name::EnchantGlovesGreaterStrength
        };
    case EquipmentSlot::CHEST:
        return {
            EnchantName::Name::EnchantChestGreaterStats
        };
    case EquipmentSlot::BOOTS:
        return {
            EnchantName::Name::EnchantBootsMinorSpeed,
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
            EnchantName::ElementalSharpeningStone,
            EnchantName::ConsecratedSharpeningStone,
            EnchantName::LesserManaOil,
            EnchantName::BrilliantManaOil,
            EnchantName::BrilliantWizardOil,
        };

        return enchants;
    }
    case EquipmentSlot::OFFHAND:
        QVector<EnchantName::Name> enchants {
            EnchantName::ConsecratedSharpeningStone,
            EnchantName::ElementalSharpeningStone,
            EnchantName::LesserManaOil,
            EnchantName::BrilliantManaOil,
            EnchantName::BrilliantWizardOil,
        };

        return enchants;
    }

    check(false, "DruidEnchants::get_available_temp_enchants reached end of switch");
    return {};
}
