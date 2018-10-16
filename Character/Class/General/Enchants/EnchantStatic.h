#ifndef ENCHANTSTATIC_H
#define ENCHANTSTATIC_H

#include "Enchant.h"
#include "ItemStatsEnum.h"
#include "EnchantName.h"

class Character;

QString get_name_from_enum(EnchantName::Name);
QString get_effect_from_enum(EnchantName::Name);

class EnchantStatic : public Enchant {
public:
    EnchantStatic(EnchantName::Name enchant_name, Character* pchar);
    virtual ~EnchantStatic() override;

private:
    EnchantName::Name enchant_name;
    Character* pchar;
};

#endif // ENCHANTSTATIC_H
