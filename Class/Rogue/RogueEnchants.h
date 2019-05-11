#ifndef ROGUEENCHANTS_H
#define ROGUEENCHANTS_H

#include "CharacterEnchants.h"

class Rogue;

class RogueEnchants: public CharacterEnchants {
public:
    RogueEnchants(Rogue* rogue);

    QVector<EnchantName::Name> get_available_enchants(const int equipment_slot) const override;
    QVector<EnchantName::Name> get_available_temp_enchants(const int equipment_slot) const override;
};

#endif // ROGUEENCHANTS_H
