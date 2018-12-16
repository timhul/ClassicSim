#ifndef WARRIORENCHANTS_H
#define WARRIORENCHANTS_H

#include "CharacterEnchants.h"
#include "ItemNamespace.h"

class Warrior;

class WarriorEnchants: public CharacterEnchants {
public:
    WarriorEnchants(Warrior* warrior);

    QVector<EnchantName::Name> get_available_enchants(const int equipment_slot) const override;
    QVector<EnchantName::Name> get_available_temp_enchants(const int equipment_slot) const override;

private:
    Warrior* warrior;

    bool has_2hand() const;
};

#endif // WARRIORENCHANTS_H
