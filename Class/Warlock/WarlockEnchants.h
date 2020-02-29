#pragma once

#include "CharacterEnchants.h"

class Warlock;

class WarlockEnchants : public CharacterEnchants {
public:
    WarlockEnchants(Warlock* warlock);

    QVector<EnchantName::Name> get_available_enchants(const int equipment_slot) const override;
    QVector<EnchantName::Name> get_available_temp_enchants(const int equipment_slot) const override;
};
