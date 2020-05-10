#include "Enchant.h"

#include <utility>

Enchant::Enchant(const EnchantName::Name enum_name, EnchantInfo* enchant_info) :
    enum_name(enum_name), name(enchant_info->get_display_name(enum_name)), effect(enchant_info->get_effect(enum_name)) {}

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
