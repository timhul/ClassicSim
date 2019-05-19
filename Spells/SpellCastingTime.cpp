#include "SpellCastingTime.h"

#include "CastComplete.h"
#include "Character.h"
#include "CharacterSpells.h"
#include "Engine.h"

SpellCastingTime::SpellCastingTime(const QString& name,
                                   const QString &icon,
                                   Character* pchar,
                                   CooldownControl* cooldown_control,
                                   bool restricted_by_gcd,
                                   const ResourceType resource_type,
                                   unsigned resource_cost,
                                   unsigned casting_time) :
    Spell(name, icon, pchar, cooldown_control, restricted_by_gcd, resource_type, resource_cost),
    casting_time_ms(casting_time),
    cast_id(std::numeric_limits<unsigned>::max())
{}

void SpellCastingTime::start_cast() {
    cast_id = pchar->get_spells()->start_cast();
    auto* new_event = new CastComplete(this, engine->get_current_priority() + get_cast_time());
    this->engine->add_event(new_event);
}

void SpellCastingTime::complete_cast() {
    pchar->get_spells()->complete_cast(cast_id);
    complete_cast_effect();
}

double SpellCastingTime::get_cast_time() const {
    return double(casting_time_ms) / 1000;
}

void SpellCastingTime::reset_effect() {
    cast_id = std::numeric_limits<unsigned>::max();
}
