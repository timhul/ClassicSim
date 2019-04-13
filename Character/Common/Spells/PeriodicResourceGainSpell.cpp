#include "PeriodicResourceGainSpell.h"

#include <utility>

#include "Character.h"
#include "Engine.h"
#include "ResourceGain.h"

PeriodicResourceGainSpell::PeriodicResourceGainSpell(const QString& name,
                                                     const QString& icon,
                                                     Character* pchar,
                                                     bool restricted_by_gcd,
                                                     double cooldown,
                                                     double tick_rate,
                                                     double tick_until,
                                                     QVector<QPair<ResourceType, unsigned>> resource_gains)
    :
      Spell(name, icon, pchar, restricted_by_gcd, cooldown, ResourceType::Rage, 0),
      tick_rate(tick_rate),
      tick_until(tick_until),
      resource_gains(std::move(resource_gains))
{}

void PeriodicResourceGainSpell::spell_effect() {
    double next_tick = engine->get_current_priority() + tick_rate;

    if (next_tick > tick_until)
        return;

    auto* new_event = new ResourceGain(pchar, this, next_tick);
    this->engine->add_event(new_event);
}

void PeriodicResourceGainSpell::perform_periodic() {
    for (auto & gain : resource_gains) {
        // TODO: Save statistics for resource gains
        switch (gain.first) {
        case ResourceType::Mana:
            pchar->gain_mana(gain.second);
            break;
        case ResourceType::Energy:
            pchar->gain_energy(gain.second);
            break;
        case ResourceType::Rage:
            pchar->gain_rage(gain.second);
            break;
        case ResourceType::Focus:
            break;
        }
    }

    spell_effect();
}
