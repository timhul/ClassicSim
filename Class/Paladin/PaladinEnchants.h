#pragma once

#include "CharacterEnchants.h"

class Paladin;

class PaladinEnchants: public CharacterEnchants {
public:
    PaladinEnchants(Paladin* paladin);

    QVector<EnchantName::Name> get_available_enchants(const int equipment_slot) const override;
    QVector<EnchantName::Name> get_available_temp_enchants(const int equipment_slot) const override;
};
