
#include "PeriodicResourceGainSpell.h"
#include "Character.h"
#include "ResourceGain.h"
#include "Engine.h"

PeriodicResourceGainSpell::PeriodicResourceGainSpell(const QString& name,
                                                     const QString& icon,
                                                     Character* pchar,
                                                     bool restricted_by_gcd,
                                                     double cooldown,
                                                     double tick_rate,
                                                     double tick_until,
                                                     QMap<Resource, unsigned> resource_gains)
    :
      Spell(name, icon, pchar, restricted_by_gcd, cooldown, 0),
      tick_rate(tick_rate),
      tick_until(tick_until),
      resource_gains(resource_gains)
{}

void PeriodicResourceGainSpell::spell_effect() {
    double next_tick = engine->get_current_priority() + tick_rate;

    if (next_tick > tick_until)
        return;

    auto* new_event = new ResourceGain(pchar, this, next_tick);
    this->engine->add_event(new_event);
}

void PeriodicResourceGainSpell::perform_periodic() {
    QMap<Resource, unsigned>::const_iterator it = resource_gains.constBegin();
    auto end = resource_gains.constEnd();

    while (it != end) {
        // TODO: Save statistics for resource gains
        switch (it.key()) {
        case Resource::Mana:
            pchar->gain_mana(it.value());
            break;
        case Resource::Energy:
            pchar->gain_energy(it.value());
            break;
        case Resource::Rage:
            pchar->gain_rage(it.value());
            break;
        }
        ++it;
    }

    spell_effect();
}
