#include "WarriorEnchants.h"

#include "Faction.h"
#include "Warrior.h"

WarriorEnchants::WarriorEnchants(Warrior* warrior) :
    warrior(warrior) {}

QVector<EnchantName::Name> WarriorEnchants::get_available_enchants(const int equipment_slot) const {
    switch (equipment_slot) {
    case EquipmentSlot::MAINHAND:
    case EquipmentSlot::OFFHAND:
        return { EnchantName::Name::Crusader, EnchantName::Name::FieryWeapon };
    case EquipmentSlot::HEAD:
    case EquipmentSlot::LEGS:
        return { EnchantName::Name::ArcanumOfRapidity, EnchantName::Name::LesserArcanumOfVoracityStrength };
    case EquipmentSlot::SHOULDERS:
        return { EnchantName::Name::MightOfTheScourge, EnchantName::Name::ZandalarSignetOfMight };
    case EquipmentSlot::BACK:
        return { EnchantName::Name::EnchantCloakLesserAgility };
    case EquipmentSlot::WRIST:
        return { EnchantName::Name::EnchantBracerSuperiorStrength };
    case EquipmentSlot::GLOVES:
        return {
            EnchantName::Name::EnchantGlovesSuperiorAgility,
            EnchantName::Name::EnchantGlovesMinorHaste,
            EnchantName::Name::EnchantGlovesGreaterStrength
        };
    case EquipmentSlot::CHEST:
        return { EnchantName::Name::EnchantChestGreaterStats };
    case EquipmentSlot::BOOTS:
        return { EnchantName::Name::EnchantBootsMinorSpeed, EnchantName::Name::EnchantBootsGreaterAgility };
    }

    assert(false);
    return {};
}

QVector<EnchantName::Name> WarriorEnchants::get_available_temp_enchants(const int equipment_slot) const {
    switch (equipment_slot) {
    case EquipmentSlot::MAINHAND: {
        QVector<EnchantName::Name> enchants { EnchantName::ElementalSharpeningStone };
        if (warrior->get_faction()->is_horde())
            enchants.prepend(EnchantName::WindfuryTotem);
        return enchants;
    }
    case EquipmentSlot::OFFHAND:
        return { EnchantName::ElementalSharpeningStone };
    }

    assert(false);
    return {};
}
