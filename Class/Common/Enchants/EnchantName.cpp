#include "EnchantName.h"

EnchantInfo::EnchantInfo() {
    enchant_specs = {
        new EnchantSpec(EnchantName::Name::ArcanumOfFocus, "Arcanum Of Focus", "Arcanum Of Focus", "+8 Spell Damage/Healing"),
        new EnchantSpec(EnchantName::Name::ArcanumOfRapidity, "Arcanum Of Rapidity", "Arcanum Of Rapidity", "+1% Haste"),
        new EnchantSpec(EnchantName::Name::Biznicks247x128Accurascope, "Biznicks 247x128 Accurascope", "Biznicks 247x128 Accurascope",
                        "+3% Ranged Hit"),
        new EnchantSpec(EnchantName::Name::BrilliantManaOil, "Brilliant Mana Oil", "Brilliant Mana Oil", "+12mp5/+25 Heal"),
        new EnchantSpec(EnchantName::Name::BrilliantWizardOil, "Brilliant Wizard Oil", "Brilliant Wizard Oil", "+36 SP\n+1% Spell Crit"),
        new EnchantSpec(EnchantName::Name::ConsecratedSharpeningStone, "Consecrated Sharpening Stone", "Consecrated Sharpening Stone",
                        "+100 AP\nvs Undead"),
        new EnchantSpec(EnchantName::Name::Crusader, "Crusader", "Enchant Weapon - Crusader", "Crusader"),
        new EnchantSpec(EnchantName::Name::DeathsEmbrace, "Death's Embrace", "Deaths Embrace", "+28 Attack and\n1% Dodge"),
        new EnchantSpec(EnchantName::Name::DenseSharpeningStone, "Dense Sharpening Stone", "Dense Sharpening Stone", "+8 Damage"),
        new EnchantSpec(EnchantName::Name::DenseWeightstone, "Dense Weightstone", "Dense Weightstone", "+8 Damage"),
        new EnchantSpec(EnchantName::Name::ElementalSharpeningStone, "Elemental Sharpening Stone", "Elemental Sharpening Stone", "+2% Crit"),
        new EnchantSpec(EnchantName::Name::Enchant2HWeaponAgility, "2H Weapon Agility", "Enchant 2H Weapon - Agility", "+25 Agility"),
        new EnchantSpec(EnchantName::Name::Enchant2HWeaponSuperiorImpact, "2H Weapon Superior Impact", "Enchant 2H Weapon - Superior Impact",
                        "+9 Damage"),
        new EnchantSpec(EnchantName::Name::EnchantBootsAgility, "Agility", "Enchant Boots - Agility", "+5 Agility"),
        new EnchantSpec(EnchantName::Name::EnchantBootsGreaterAgility, "Greater Agility", "Enchant Boots - Greater Agility", "+7 Agility"),
        new EnchantSpec(EnchantName::Name::EnchantBootsMinorSpeed, "Minor Speed", "Enchant Boots - Minor Speed", "Speed Increase"),
        new EnchantSpec(EnchantName::Name::EnchantBootsSpirit, "Spirit", "Enchant Boots - Spirit", "+5 Spirit"),
        new EnchantSpec(EnchantName::Name::EnchantBracerGreaterIntellect, "Greater Intellect", "Enchant Bracer - Greater Intellect", "+7 Intellect"),
        new EnchantSpec(EnchantName::Name::EnchantBracerGreaterStrength, "Greater Strength", "Enchant Bracer - Greater - Strength", "+7 Strength"),
        new EnchantSpec(EnchantName::Name::EnchantBracerManaRegeneration, "Mana Regeneration", "Enchant Bracer - Mana Regeneration", "+4 mp5"),
        new EnchantSpec(EnchantName::Name::EnchantBracerMinorAgility, "Minor Agility", "Enchant Bracer - Minor Agility", "+1 Agility"),
        new EnchantSpec(EnchantName::Name::EnchantBracerSuperiorStrength, "Superior Strength", "Enchant Bracer - Superior Strength", "+9 Strength"),
        new EnchantSpec(EnchantName::Name::EnchantChestGreaterStats, "Greater Stats", "Enchant Chest - Greater Stats", "+4 Attributes"),
        new EnchantSpec(EnchantName::Name::EnchantChestMajorMana, "Major Mana", "Enchant Chest - Major Mana", "+100 Mana"),
        new EnchantSpec(EnchantName::Name::EnchantChestStats, "Stats", "Enchant Chest - Stats", "+3 Attributes"),
        new EnchantSpec(EnchantName::Name::EnchantCloakLesserAgility, "Lesser Agility", "Enchant Cloak - Lesser Agility", "+3 Agility"),
        new EnchantSpec(EnchantName::Name::EnchantGlovesFirePower, "Fire Power", "Enchant Gloves - Fire Power", "+20 Fire Damage"),
        new EnchantSpec(EnchantName::Name::EnchantGlovesFrostPower, "Frost Power", "Enchant Gloves - Frost Power", "+20 Frost Damage"),
        new EnchantSpec(EnchantName::Name::EnchantGlovesShadowPower, "Shadow Power", "Enchant Gloves - Shadow Power", "+20 Shadow Damage"),
        new EnchantSpec(EnchantName::Name::EnchantGlovesGreaterAgility, "Greater Agility", "Enchant Gloves - Greater Agility", "+7 Agility"),
        new EnchantSpec(EnchantName::Name::EnchantGlovesGreaterStrength, "Greater Strength", "Enchant Gloves - Greater Strength", "+7 Strength"),
        new EnchantSpec(EnchantName::Name::EnchantGlovesMinorHaste, "Minor Haste", "Enchant Gloves - Minor Haste", "+1% Attack Speed"),
        new EnchantSpec(EnchantName::Name::EnchantGlovesSuperiorAgility, "Superior Agility", "Enchant Gloves - Superior Agility", "+15 Agility"),
        new EnchantSpec(EnchantName::Name::EnchantWeaponAgility, "Agility", "Enchant Weapon - Agility", "+15 Agility"),
        new EnchantSpec(EnchantName::Name::EnchantWeaponSpellPower, "Spell Power", "Enchant Weapon - Spell Power", "+30 Spell Damage/Healing"),
        new EnchantSpec(EnchantName::Name::EnchantWeaponStrength, "Strength", "Enchant Weapon - Strength", "+15 Strength"),
        new EnchantSpec(EnchantName::Name::FalconsCall, "Falcon's Call", "Falcons Call", "+24 Ranged Attack Power\n10 Stamina, +1% Hit"),
        new EnchantSpec(EnchantName::Name::FieryWeapon, "Fiery Weapon", "Enchant Weapon - Fiery Weapon", "Fiery Weapon"),
        new EnchantSpec(EnchantName::Name::InstantPoison, "Instant Poison", "Instant Poison", "Instant Poison"),
        new EnchantSpec(EnchantName::Name::IronCounterweight, "Iron Counterweight", "Iron Counterweight", "+3% Attack Speed"),
        new EnchantSpec(EnchantName::Name::LesserArcanumOfVoracityAgility, "Lesser Arcanum Of Voracity - Agility",
                        "Lesser Arcanum Of Voracity - Agility", "+8 Agility"),
        new EnchantSpec(EnchantName::Name::LesserArcanumOfVoracityIntellect, "Lesser Arcanum Of Voracity - Intellect",
                        "Lesser Arcanum Of Voracity - Intellect", "+8 Intellect"),
        new EnchantSpec(EnchantName::Name::LesserArcanumOfVoracitySpirit, "Lesser Arcanum Of Voracity - Spirit",
                        "Lesser Arcanum Of Voracity - Spirit", "+8 Spirit"),
        new EnchantSpec(EnchantName::Name::LesserArcanumOfVoracityStamina, "Lesser Arcanum Of Voracity - Stamina",
                        "Lesser Arcanum Of Voracity - Stamina", "+8 Stamina"),
        new EnchantSpec(EnchantName::Name::LesserArcanumOfVoracityStrength, "Lesser Arcanum Of Voracity - Strength",
                        "Lesser Arcanum Of Voracity - Strength", "+8 Strength"),
        new EnchantSpec(EnchantName::Name::LesserManaOil, "Lesser Mana Oil", "Lesser Mana Oil", "+8 mp5"),
        new EnchantSpec(EnchantName::Name::MightOfTheScourge, "Might of the Scourge", "Might of the Scourge", "+1% Crit and\n+26 Attack Power"),
        new EnchantSpec(EnchantName::Name::PowerOfTheScourge, "Power Of The Scourge", "Power Of The Scourge",
                        "+15 Spell Damage/Healing\n+1% Spell Crit"),
        new EnchantSpec(EnchantName::Name::PresenceOfSight, "Presence Of Sight", "Presence Of Sight", "+18 Spell Damage/Healing\n+1% Spell Hit"),
        new EnchantSpec(EnchantName::Name::HoodooHex, "Hoodoo Hex", "Hoodoo Hex", "+18 Spell Damage/Healing\n+10 Stamina"),
        new EnchantSpec(EnchantName::Name::ShadowOil, "Shadow Oil", "Shadow Oil", "15% R3 Shadow Bolt"),
        new EnchantSpec(EnchantName::Name::SniperScope, "Sniper Scope", "Sniper Scope", "+7 Damage"),
        new EnchantSpec(EnchantName::Name::SolidWeightstone, "Solid Weightstone", "Solid Weightstone", "+6 Damage"),
        new EnchantSpec(EnchantName::Name::SuperiorStriking, "Superior Striking", "Enchant Weapon - Superior Striking", "+5 Damage"),
        new EnchantSpec(EnchantName::Name::WindfuryTotem, "Windfury Totem", "Windfury Totem", "Windfury"),
        new EnchantSpec(EnchantName::Name::ZandalarSignetOfMight, "Zandalar Signet Of Might", "Zandalar Signet Of Might", "+30 Attack Power"),
        new EnchantSpec(EnchantName::Name::ZandalarSignetOfMojo, "Zandalar Signet Of Mojo", "Zandalar Signet Of Mojo", "+18 Spell Damage/Healing"),
    };
}

EnchantInfo::~EnchantInfo() {
    for (const auto& spec : enchant_specs)
        delete spec;
}

QString EnchantInfo::get_display_name(EnchantName::Name enum_val) const {
    for (const auto& spec : enchant_specs) {
        if (spec->enum_name == enum_val)
            return spec->display_name;
    }

    return "<failed to find enchant info>";
}

QString EnchantInfo::get_unique_name(EnchantName::Name enum_val) const {
    for (const auto& spec : enchant_specs) {
        if (spec->enum_name == enum_val)
            return spec->unique_name;
    }

    return "<failed to find enchant info>";
}

QString EnchantInfo::get_effect(EnchantName::Name enum_val) const {
    for (const auto& spec : enchant_specs) {
        if (spec->enum_name == enum_val)
            return spec->effect;
    }

    return "<failed to find enchant info>";
}

EnchantName::Name EnchantInfo::get_enum_val(const QString& unique_name) const {
    for (const auto& spec : enchant_specs) {
        if (spec->unique_name == unique_name)
            return spec->enum_name;
    }

    return EnchantName::Name::NoEnchant;
}
