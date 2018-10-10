
#include "SpellCastingTime.h"
#include "CastComplete.h"

SpellCastingTime::SpellCastingTime(const QString& name,
                                   Character* pchar,
                                   bool restricted_by_gcd,
                                   double cooldown,
                                   int resource_cost,
                                   int casting_time) :
    Spell(name, pchar, restricted_by_gcd, cooldown, resource_cost),
    casting_time_ms(casting_time),
    start_cast_timestamp(0),
    complete_cast_timestamp(-1)
{}

void SpellCastingTime::start_cast() {
    start_cast_timestamp = engine->get_current_priority();
    complete_cast_timestamp = start_cast_timestamp + get_cast_time();
    auto* new_event = new CastComplete(this, complete_cast_timestamp);
    this->engine->add_event(new_event);
}

void SpellCastingTime::complete_cast() {
    complete_cast_timestamp = -1;
    complete_cast_effect();
}

double SpellCastingTime::get_cast_time() const {
    return double(casting_time_ms) / 1000;
}

bool SpellCastingTime::cast_in_progress() const {
    return complete_cast_timestamp > engine->get_current_priority();
}

bool SpellCastingTime::is_ready_spell_specific() const {
    return !cast_in_progress();
}
