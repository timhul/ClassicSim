#pragma once

#include "CharacterEnchants.h"

class Shaman;

class ShamanEnchants: public CharacterEnchants {
public:
    ShamanEnchants(Shaman* shaman);

    QVector<EnchantName::Name> get_available_enchants(const int equipment_slot) const override;
    QVector<EnchantName::Name> get_available_temp_enchants(const int equipment_slot) const override;
};
