#include "RogueEnchants.h"

#include "Faction.h"
#include "Rogue.h"
#include "Utils/Check.h"

RogueEnchants::RogueEnchants(Rogue* rogue) : CharacterEnchants(rogue) {}

QVector<EnchantName::Name> RogueEnchants::get_available_enchants(const int equipment_slot) const {
    switch (equipment_slot) {
    case EquipmentSlot::MAINHAND:
    case EquipmentSlot::OFFHAND:
        return {EnchantName::Name::Crusader, EnchantName::Name::FieryWeapon, EnchantName::Name::EnchantWeaponStrength,
                EnchantName::Name::SuperiorStriking, EnchantName::Name::EnchantWeaponAgility};
    case EquipmentSlot::RANGED:
        return {};
    case EquipmentSlot::HEAD:
    case EquipmentSlot::LEGS:
        return {EnchantName::Name::ArcanumOfRapidity, EnchantName::Name::LesserArcanumOfVoracityAgility, EnchantName::Name::DeathsEmbrace};
    case EquipmentSlot::SHOULDERS:
        return {EnchantName::Name::MightOfTheScourge, EnchantName::Name::ZandalarSignetOfMight};
    case EquipmentSlot::BACK:
        return {EnchantName::Name::EnchantCloakLesserAgility};
    case EquipmentSlot::WRIST:
        return {EnchantName::Name::EnchantBracerGreaterStrength, EnchantName::Name::EnchantBracerSuperiorStrength, EnchantName::Name::EnchantBracerMinorAgility};
    case EquipmentSlot::GLOVES:
        return {EnchantName::Name::EnchantGlovesSuperiorAgility, EnchantName::Name::EnchantGlovesGreaterAgility,
                EnchantName::Name::EnchantGlovesMinorHaste, EnchantName::Name::EnchantGlovesGreaterStrength};
    case EquipmentSlot::CHEST:
        return {
            EnchantName::Name::EnchantChestStats,
            EnchantName::Name::EnchantChestGreaterStats,
        };
    case EquipmentSlot::BOOTS:
        return {EnchantName::Name::EnchantBootsMinorSpeed, EnchantName::Name::EnchantBootsAgility, EnchantName::Name::EnchantBootsGreaterAgility};
    }

    check(false, "RogueEnchants::get_available_enchants reached end of switch");
    return {};
}

QVector<EnchantName::Name> RogueEnchants::get_available_temp_enchants(const int equipment_slot) const {
    switch (equipment_slot) {
    case EquipmentSlot::MAINHAND: {
        QVector<EnchantName::Name> enchants {
            EnchantName::Name::ElementalSharpeningStone,
            EnchantName::Name::ConsecratedSharpeningStone,
            EnchantName::Name::InstantPoison,
            EnchantName::Name::ShadowOil,
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
            EnchantName::Name::ConsecratedSharpeningStone,
            EnchantName::Name::ElementalSharpeningStone,
            EnchantName::Name::InstantPoison,
            EnchantName::Name::ShadowOil,
        };
        if (has_sharp_weapon(equipment_slot))
            enchants.prepend(EnchantName::Name::DenseSharpeningStone);
        else if (has_blunt_weapon(equipment_slot))
            enchants.prepend(EnchantName::Name::SolidWeightstone);
        return enchants;
    }

    check(false, "RogueEnchants::get_available_temp_enchants reached end of switch");
    return {};
}
