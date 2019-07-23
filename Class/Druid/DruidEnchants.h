#pragma once

#include "CharacterEnchants.h"

class Druid;

class DruidEnchants: public CharacterEnchants {
public:
    DruidEnchants(Druid* Druid);

    QVector<EnchantName::Name> get_available_enchants(const int equipment_slot) const override;
    QVector<EnchantName::Name> get_available_temp_enchants(const int equipment_slot) const override;
};
