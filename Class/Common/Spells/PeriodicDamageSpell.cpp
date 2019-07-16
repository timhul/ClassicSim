#include "PeriodicDamageSpell.h"

#include "Character.h"
#include "CharacterStats.h"
#include "MagicSchools.h"
#include "NoEffectUniqueDebuff.h"

PeriodicDamageSpell::PeriodicDamageSpell(const QString& name,
                                         const QString& icon,
                                         Character* pchar,
                                         const Priority priority,
                                         const RestrictedByGcd restricted_by_gcd,
                                         const MagicSchool school,
                                         const double tick_rate,
                                         const int duration,
                                         const unsigned full_duration_dmg,
                                         const unsigned resource_cost,
                                         const double cast_time_ms,
                                         const double spell_coefficient)
    :
      SpellPeriodic(name, icon, pchar,
                    new NoEffectUniqueDebuff(pchar, priority, duration, name, icon, Hidden::No),
                    restricted_by_gcd,
                    ResourceType::Mana,
                    tick_rate,
                    0,
                    0),
      school(school),
      full_duration_dmg(full_duration_dmg),
      duration(duration),
      spell_coefficient(spell_coefficient),
      num_ticks(duration / tick_rate),
      reported_resource_cost(resource_cost / num_ticks),
      reported_execution_time(cast_time_ms / num_ticks / 1000)
{}

PeriodicDamageSpell::~PeriodicDamageSpell() {
    delete marker_buff;
}

double PeriodicDamageSpell::get_spell_coefficient_from_duration(const double duration) {
    return duration / 15;
}

bool PeriodicDamageSpell::check_application_success() {
    return true;
}

void PeriodicDamageSpell::new_application_effect() {

}

void PeriodicDamageSpell::refresh_effect() {

}

void PeriodicDamageSpell::tick_effect() {
    const double spell_power_bonus = pchar->get_stats()->get_spell_damage(school) * spell_coefficient;
    const double damage_dealt = (full_duration_dmg + spell_power_bonus) * pchar->get_stats()->get_magic_school_damage_mod(school) / num_ticks + tick_rest;
    tick_rest += damage_dealt - round(damage_dealt);

    add_hit_dmg(static_cast<int>(round(damage_dealt)), reported_resource_cost, reported_execution_time);

    add_next_tick();
}

void PeriodicDamageSpell::reset_effect() {
    tick_rest = 0;
}
