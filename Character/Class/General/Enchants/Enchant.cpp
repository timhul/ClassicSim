
#include "Enchant.h"

Enchant::Enchant(const QString &name, const QString &effect_string) :
    name(name), effect(effect_string)
{}

Enchant::~Enchant() = default;

QString Enchant::get_name() const {
    return this->name;
}

QString Enchant::get_effect() const {
    return this->effect;
}
