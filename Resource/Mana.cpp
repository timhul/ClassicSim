#include "Mana.h"

#include "Character.h"
#include "CharacterStats.h"
#include "Engine.h"
#include "Utils/Check.h"
#include "Utils/CompareDouble.h"

Mana::Mana(Character* pchar) :
    RegeneratingResource(pchar)
{}

void Mana::set_base_mana(const unsigned base_mana) {
    this->base_mana = base_mana;
    reset_resource();
}

unsigned Mana::get_max_resource() const {
    return base_mana + pchar->get_stats()->get_intellect() * 15;
}

unsigned Mana::get_resource_per_tick() {
    double mp5 = static_cast<double>(pchar->get_stats()->get_mp5());

    if (lhs_almost_equal_or_less(5.0, pchar->get_engine()->get_current_priority() - last_use_of_mana))
        mp5 += pchar->get_mp5_from_spirit();
    else
        mp5 += pchar->get_mp5_from_spirit() * mp5_from_spirit_within_5sr_modifier;

    double mp2 = mp5 / 5 * 2;
    mp2 += remainder;

    remainder = mp2 - floor(mp2);

    return static_cast<unsigned>(floor(mp2));
}

ResourceType Mana::get_resource_type() const {
    return ResourceType::Mana;
}

double Mana::get_tick_rate() const {
    return 2.0;
}

void Mana::lose_resource_effect() {
    last_use_of_mana = pchar->get_engine()->get_current_priority();
}

void Mana::reset_effect() {
    last_use_of_mana = 0;
    remainder = 0;
}
