#include "WarriorEnchants.h"

#include "Equipment.h"
#include "Faction.h"
#include "Warrior.h"
#include "Weapon.h"

WarriorEnchants::WarriorEnchants(Warrior* warrior) :
    warrior(warrior) {}

QVector<EnchantName::Name> WarriorEnchants::get_available_enchants(const int equipment_slot) const {
    switch (equipment_slot) {
    case EquipmentSlot::MAINHAND: {
        QVector<EnchantName::Name> enchants {
            EnchantName::Name::Crusader,
            EnchantName::Name::FieryWeapon,
            EnchantName::Name::EnchantWeaponStrength,
            EnchantName::Name::SuperiorStriking
        };

        if (has_2hand()) {
            enchants.append({
                                EnchantName::Name::Enchant2HWeaponAgility,
                                EnchantName::Name::Enchant2HWeaponSuperiorImpact,
                                EnchantName::Name::IronCounterweight,
                            });
        }
        else
           enchants.append(EnchantName::Name::EnchantWeaponAgility);

        return enchants;
    }
    case EquipmentSlot::OFFHAND: {
        return {
            EnchantName::Name::Crusader,
            EnchantName::Name::FieryWeapon,
            EnchantName::Name::EnchantWeaponStrength,
            EnchantName::Name::SuperiorStriking,
            EnchantName::Name::EnchantWeaponAgility
        };
    }
    case EquipmentSlot::HEAD:
    case EquipmentSlot::LEGS:
        return {
            EnchantName::Name::ArcanumOfRapidity,
            EnchantName::Name::LesserArcanumOfVoracityStrength
        };
    case EquipmentSlot::SHOULDERS:
        return {
            EnchantName::Name::MightOfTheScourge,
            EnchantName::Name::ZandalarSignetOfMight
        };
    case EquipmentSlot::BACK:
        return {
            EnchantName::Name::EnchantCloakLesserAgility
        };
    case EquipmentSlot::WRIST:
        return {
            EnchantName::Name::EnchantBracerSuperiorStrength
        };
    case EquipmentSlot::GLOVES:
        return {
            EnchantName::Name::EnchantGlovesSuperiorAgility,
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
            EnchantName::Name::EnchantBootsGreaterAgility
        };
    }

    assert(false);
    return {};
}

QVector<EnchantName::Name> WarriorEnchants::get_available_temp_enchants(const int equipment_slot) const {
    switch (equipment_slot) {
    case EquipmentSlot::MAINHAND: {
        QVector<EnchantName::Name> enchants {
            EnchantName::ElementalSharpeningStone,
            EnchantName::ConsecratedSharpeningStone
        };
        if (warrior->get_faction()->is_horde())
            enchants.prepend(EnchantName::WindfuryTotem);
        return enchants;
    }
    case EquipmentSlot::OFFHAND:
        return {
            EnchantName::ElementalSharpeningStone,
            EnchantName::ConsecratedSharpeningStone
        };
    }

    assert(false);
    return {};
}

bool WarriorEnchants::has_2hand() const {
    if (warrior->get_equipment()->get_mainhand() == nullptr)
        return false;

    return warrior->get_equipment()->get_mainhand()->is_2hand();
}
