#ifndef CHARACTERENCHANTS_H
#define CHARACTERENCHANTS_H

#include <QVector>

#include "EnchantName.h"

class CharacterEnchants {
public:
    virtual ~CharacterEnchants() = default;

    virtual QVector<EnchantName::Name> get_available_enchants(const int equipment_slot) const = 0;
    virtual QVector<EnchantName::Name> get_available_temp_enchants(const int equipment_slot) const = 0;
};

#endif // CHARACTERENCHANTS_H
