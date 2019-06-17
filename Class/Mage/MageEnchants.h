#pragma once


#include "CharacterEnchants.h"

class Mage;

class MageEnchants: public CharacterEnchants {
public:
    MageEnchants(Mage* mage);

    QVector<EnchantName::Name> get_available_enchants(const int equipment_slot) const override;
    QVector<EnchantName::Name> get_available_temp_enchants(const int equipment_slot) const override;
};

