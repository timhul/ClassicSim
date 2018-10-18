
#include "Enchant.h"

Enchant::Enchant(const EnchantName::Name enum_name, const QString &name, const QString &effect_string) :
    enum_name(enum_name), name(name), effect(effect_string)
{}

Enchant::~Enchant() = default;

EnchantName::Name Enchant::get_enum_name() const {
    return this->enum_name;
}

QString Enchant::get_name() const {
    return this->name;
}

QString Enchant::get_effect() const {
    return this->effect;
}
