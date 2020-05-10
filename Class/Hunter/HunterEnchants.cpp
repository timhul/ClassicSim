#include "HunterEnchants.h"

#include "Faction.h"
#include "Hunter.h"
#include "Utils/Check.h"

HunterEnchants::HunterEnchants(Hunter* hunter) : CharacterEnchants(hunter) {}

QVector<EnchantName::Name> HunterEnchants::get_available_enchants(const int equipment_slot) const {
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
    case EquipmentSlot::OFFHAND: {
        return {EnchantName::Name::Crusader, EnchantName::Name::FieryWeapon, EnchantName::Name::EnchantWeaponStrength,
                EnchantName::Name::SuperiorStriking, EnchantName::Name::EnchantWeaponAgility};
    }
    case EquipmentSlot::RANGED:
        return {
            EnchantName::Name::Biznicks247x128Accurascope,
            EnchantName::Name::SniperScope,
        };
    case EquipmentSlot::HEAD:
    case EquipmentSlot::LEGS:
        return {
            EnchantName::Name::ArcanumOfRapidity,
            EnchantName::Name::LesserArcanumOfVoracityAgility,
            EnchantName::Name::ArcanumOfFocus,
            EnchantName::Name::FalconsCall,
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
            EnchantName::Name::EnchantBracerManaRegeneration,
            EnchantName::Name::EnchantBracerGreaterStrength,
            EnchantName::Name::EnchantBracerSuperiorStrength,
            EnchantName::Name::EnchantBracerMinorAgility,
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

    check(false, "HunterEnchants::get_available_enchants reached end of switch");
    return {};
}

QVector<EnchantName::Name> HunterEnchants::get_available_temp_enchants(const int equipment_slot) const {
    switch (equipment_slot) {
    case EquipmentSlot::MAINHAND: {
        QVector<EnchantName::Name> enchants {
            EnchantName::Name::ElementalSharpeningStone, EnchantName::Name::ConsecratedSharpeningStone, EnchantName::Name::LesserManaOil,
            EnchantName::Name::BrilliantManaOil,         EnchantName::Name::BrilliantWizardOil,
        };
        if (has_sharp_weapon(equipment_slot))
            enchants.prepend(EnchantName::Name::DenseSharpeningStone);
        else if (has_blunt_weapon(equipment_slot)) {
            enchants.prepend(EnchantName::Name::DenseWeightstone);
            enchants.prepend(EnchantName::Name::SolidWeightstone);
        }

        if (pchar->get_faction()->is_horde())
            enchants.prepend(EnchantName::Name::WindfuryTotem);
        return enchants;
    }
    case EquipmentSlot::OFFHAND:
        QVector<EnchantName::Name> enchants {
            EnchantName::Name::ConsecratedSharpeningStone, EnchantName::Name::ElementalSharpeningStone, EnchantName::Name::LesserManaOil,
            EnchantName::Name::BrilliantManaOil,           EnchantName::Name::BrilliantWizardOil,
        };
        if (has_sharp_weapon(equipment_slot))
            enchants.prepend(EnchantName::Name::DenseSharpeningStone);
        else if (has_blunt_weapon(equipment_slot))
            enchants.prepend(EnchantName::Name::SolidWeightstone);
        return enchants;
    }

    check(false, "HunterEnchants::get_available_temp_enchants reached end of switch");
    return {};
}
