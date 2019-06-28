#pragma once

#include "CharacterEnchants.h"

class Warrior;

class WarriorEnchants: public CharacterEnchants {
public:
    WarriorEnchants(Warrior* warrior);

    QVector<EnchantName::Name> get_available_enchants(const int equipment_slot) const override;
    QVector<EnchantName::Name> get_available_temp_enchants(const int equipment_slot) const override;
};
