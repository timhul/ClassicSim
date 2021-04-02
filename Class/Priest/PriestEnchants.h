#pragma once

#include "CharacterEnchants.h"

class Priest;

class PriestEnchants : public CharacterEnchants {
public:
    PriestEnchants(Priest* priest);

    QVector<EnchantName::Name> get_available_enchants(const int equipment_slot) const override;
    QVector<EnchantName::Name> get_available_temp_enchants(const int equipment_slot) const override;
};
