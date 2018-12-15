#include "RogueEnchants.h"

#include "Faction.h"
#include "Rogue.h"

RogueEnchants::RogueEnchants(Rogue* rogue) :
    rogue(rogue) {}

QVector<EnchantName::Name> RogueEnchants::get_available_enchants(const int equipment_slot) const {
    switch (equipment_slot) {
    case EquipmentSlot::MAINHAND:
    case EquipmentSlot::OFFHAND:
        return { EnchantName::Name::Crusader, EnchantName::Name::FieryWeapon };
    case EquipmentSlot::HEAD:
    case EquipmentSlot::LEGS:
        return { EnchantName::Name::ArcanumOfRapidity, EnchantName::Name::LesserArcanumOfVoracityAgility };
    }

    assert(false);
    return {};
}

QVector<EnchantName::Name> RogueEnchants::get_available_temp_enchants(const int equipment_slot) const {
    switch (equipment_slot) {
    case EquipmentSlot::MAINHAND: {
        QVector<EnchantName::Name> enchants { EnchantName::ElementalSharpeningStone, EnchantName::InstantPoison };
        if (rogue->get_faction()->is_horde())
            enchants.prepend(EnchantName::WindfuryTotem);
        return enchants;
    }
    case EquipmentSlot::OFFHAND:
        return { EnchantName::ElementalSharpeningStone, EnchantName::InstantPoison };
    }

    assert(false);
    return {};
}
