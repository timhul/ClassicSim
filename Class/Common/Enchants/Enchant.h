#pragma once

#include <QString>

#include "EnchantName.h"

class Enchant {
public:
    Enchant(const EnchantName::Name enum_name, EnchantInfo* enchant_info);
    virtual ~Enchant();

    EnchantName::Name get_enum_name() const;
    QString get_name() const;
    QString get_effect() const;

protected:
    EnchantName::Name enum_name;
    QString name;
    QString effect;
};
