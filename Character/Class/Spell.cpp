
#include "Spell.h"
#include "AttackResult.h"
#include "Character.h"

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

    float delta = get_next_use() - target_timestamp;
    if (delta < 0.0001)
        return true;

    return target_timestamp >= get_next_use();
}

bool Spell::cooldown_greater_than(const float value) const {
    // Note that this function actually returns GEQ and not greater.
    return !cooldown_less_than(value);
}

int Spell::perform(const int resource_level) {
    assert(resource_level >= resource_cost);
    last_used = engine->get_current_priority();
    return this->spell_effect(resource_level);
}

void Spell::add_spell_cd_event(void) const {
    float cooldown_ready = engine->get_current_priority() + cooldown;
    CooldownReady* new_event = new CooldownReady(pchar, cooldown_ready);
    engine->add_event(new_event);
}

void Spell::add_gcd_event(void) const {
    float gcd_ready = engine->get_current_priority() + pchar->global_cooldown();
    CooldownReady* new_event = new CooldownReady(pchar, gcd_ready);
    engine->add_event(new_event);
}

void Spell::add_fail_stats(std::string outcome) const {
    engine->get_statistics()->increment(get_name() + outcome);
}

void Spell::add_success_stats(std::string outcome,
                                    const int damage_dealt) const {
    engine->get_statistics()->increment(get_name() + outcome);
    engine->get_statistics()->add("Total Damage", damage_dealt);
    engine->get_statistics()->add(get_name() + outcome + " Damage", damage_dealt);
}

void Spell::add_success_stats(std::string outcome,
                                       const int damage_dealt,
                                       const int rage_gained) const {
    engine->get_statistics()->increment(get_name() + outcome);
    engine->get_statistics()->add("Total Damage", damage_dealt);
    engine->get_statistics()->add(get_name() + outcome + " Damage", damage_dealt);
    engine->get_statistics()->add(get_name() + outcome + " Rage Gain", rage_gained);
}
