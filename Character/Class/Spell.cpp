
#include "Spell.h"

std::string Spell::get_name() const {
    return this->name;
}

float Spell::get_cooldown() {
    return this->cooldown;
}

float Spell::get_last_used() {
    return this->last_used;
}

float Spell::get_next_use() const {
    return last_used + cooldown;
}

bool Spell::is_ready() const {
    return cooldown_less_than(0);
}

bool Spell::is_available(const int resource_level) const {
    return is_ready() && resource_level >= this->resource_cost;
}

bool Spell::cooldown_less_than(const float value) const {
    const float curr = engine->get_current_priority();
    float target_timestamp = curr + value;

    return target_timestamp >= get_next_use();
}

bool Spell::cooldown_greater_than(const float value) const {
    // Note that this function actually returns GEQ and not greater.
    return !cooldown_less_than(value);
}

int Spell::perform(const int resource_level) const {
    assert(resource_level >= resource_cost);
    return this->spell_effect(resource_level);
}
