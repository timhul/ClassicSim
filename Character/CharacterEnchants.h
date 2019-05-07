#ifndef CHARACTERENCHANTS_H
#define CHARACTERENCHANTS_H

#include <QVector>

#include "EnchantName.h"
#include "ItemNamespace.h"

class Character;

class CharacterEnchants {
public:
    CharacterEnchants(Character* pchar);
    virtual ~CharacterEnchants() = default;

    virtual QVector<EnchantName::Name> get_available_enchants(const int equipment_slot) const = 0;
    virtual QVector<EnchantName::Name> get_available_temp_enchants(const int equipment_slot) const = 0;

    bool enchant_valid(EnchantName::Name enchant_name, const int weapon_slot) const;
    bool temp_enchant_valid(EnchantName::Name enchant_name, const int weapon_slot, const int equipment_slot) const;

protected:
    Character* pchar;

    bool has_sharp_weapon(const int equipment_slot) const;
    bool has_2hand() const;
};

#endif // CHARACTERENCHANTS_H
