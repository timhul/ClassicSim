#pragma once

#include "CharacterEnchants.h"

class Hunter;

class HunterEnchants: public CharacterEnchants {
public:
    HunterEnchants(Hunter* hunter);

    QVector<EnchantName::Name> get_available_enchants(const int equipment_slot) const override;
    QVector<EnchantName::Name> get_available_temp_enchants(const int equipment_slot) const override;
};
