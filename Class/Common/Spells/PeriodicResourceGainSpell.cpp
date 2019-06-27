#include "PeriodicResourceGainSpell.h"

#include <utility>

#include "Character.h"
#include "ClassStatistics.h"
#include "CooldownControl.h"
#include "Engine.h"
#include "ResourceGain.h"
#include "StatisticsResource.h"

PeriodicResourceGainSpell::PeriodicResourceGainSpell(const QString& name,
                                                     const QString& icon,
                                                     Character* pchar,
                                                     bool restricted_by_gcd,
                                                     double cooldown,
                                                     double tick_rate,
                                                     double tick_until,
                                                     QVector<QPair<ResourceType, unsigned>> resource_gains)
    :
      Spell(name, icon, pchar, new CooldownControl(pchar, cooldown), restricted_by_gcd, ResourceType::Rage, 0),
      tick_rate(tick_rate),
      tick_until(tick_until),
      resource_gains(std::move(resource_gains))
{}

PeriodicResourceGainSpell::~PeriodicResourceGainSpell() {
    delete cooldown;
}

void PeriodicResourceGainSpell::spell_effect() {
    double next_tick = engine->get_current_priority() + tick_rate;

    if (next_tick > tick_until)
        return;

    auto* new_event = new ResourceGain(this, next_tick);
    this->engine->add_event(new_event);
}

void PeriodicResourceGainSpell::perform_periodic() {
    for (const auto & gain : resource_gains) {
        unsigned before_gain;
        unsigned delta = 0;
        before_gain = pchar->get_resource_level(gain.first);
        switch (gain.first) {
        case ResourceType::Mana:
            pchar->gain_mana(gain.second);
            delta = pchar->get_resource_level(gain.first) - before_gain;
            break;
        case ResourceType::Energy:
            pchar->gain_energy(gain.second);
            delta = pchar->get_resource_level(gain.first) - before_gain;
            break;
        case ResourceType::Rage:
            pchar->gain_rage(gain.second);
            delta = pchar->get_resource_level(gain.first) - before_gain;
            break;
        case ResourceType::Focus:
            pchar->gain_focus(gain.second);
            delta = pchar->get_resource_level(gain.first) - before_gain;
            break;
        }

        if (delta > 0)
            statistics_resource->add_resource_gain(gain.first, delta);
    }

    spell_effect();
}

void PeriodicResourceGainSpell::prepare_set_of_combat_iterations_spell_specific() {
    this->statistics_resource = pchar->get_statistics()->get_resource_statistics(name, icon);
}
