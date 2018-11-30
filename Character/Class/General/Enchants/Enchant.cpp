#include "Enchant.h"

#include <utility>

Enchant::Enchant(const EnchantName::Name enum_name, QString name, QString effect_string) :
    enum_name(enum_name), name(std::move(name)), effect(std::move(effect_string))
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
