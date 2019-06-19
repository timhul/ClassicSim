#include "SpellCastingTime.h"

#include "CastComplete.h"
#include "Character.h"
#include "CharacterSpells.h"
#include "Engine.h"
#include "Utils/CompareDouble.h"

SpellCastingTime::SpellCastingTime(const QString& name,
                                   const QString &icon,
                                   Character* pchar,
                                   CooldownControl* cooldown_control,
                                   bool restricted_by_gcd,
                                   const ResourceType resource_type,
                                   unsigned resource_cost,
                                   int spell_rank) :
    Spell(name, icon, pchar, cooldown_control, restricted_by_gcd, resource_type, resource_cost, spell_rank),
    casting_time_ms(std::numeric_limits<unsigned>::max()),
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

double SpellCastingTime::spell_coefficient_from_casting_time() const {
    if (casting_time_ms < 1500)
        return 1500 / 3500;
    if (casting_time_ms > 3000)
        return 1.0;

    const double base_coefficient = static_cast<double>(casting_time_ms) / 3500;
    if (level_req >= 20)
        return base_coefficient;

    return std::max(0.0, base_coefficient - (20 - level_req) * 0.0375);
}
