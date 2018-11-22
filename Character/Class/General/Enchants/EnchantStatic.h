#ifndef ENCHANTSTATIC_H
#define ENCHANTSTATIC_H

#include "Enchant.h"
#include "EnchantName.h"
#include "ItemNamespace.h"
#include "ItemStatsEnum.h"

class Character;

QString get_name_from_enum(EnchantName::Name);
QString get_effect_from_enum(EnchantName::Name);

class EnchantStatic : public Enchant {
public:
    EnchantStatic(EnchantName::Name enchant_name, Character* pchar, int enchant_slot);
    virtual ~EnchantStatic() override;

private:
    EnchantName::Name enchant_name;
    Character* pchar;
    int enchant_slot;
};

#endif // ENCHANTSTATIC_H
