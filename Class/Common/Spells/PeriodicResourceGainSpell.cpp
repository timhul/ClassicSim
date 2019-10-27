#include "PeriodicResourceGainSpell.h"

#include "Character.h"
#include "ClassStatistics.h"
#include "NoEffectSelfBuff.h"
#include "StatisticsResource.h"

PeriodicResourceGainSpell::PeriodicResourceGainSpell(const QString& name,
                                                     const QString& icon,
                                                     Character* pchar,
                                                     const RestrictedByGcd restricted_by_gcd,
                                                     const double tick_rate,
                                                     const int duration,
                                                     QVector<QPair<ResourceType, unsigned>> resource_gains)
    :
      SpellPeriodic(name, icon, pchar,
                    new NoEffectSelfBuff(pchar, duration, name, icon, Hidden::No),
                    restricted_by_gcd,
                    ResourceType::Mana,
                    tick_rate,
                    0,
                    0),
      resource_gains(std::move(resource_gains))
{}

PeriodicResourceGainSpell::~PeriodicResourceGainSpell() {
    if (marker_buff->is_enabled())
        marker_buff->disable_buff();

    delete marker_buff;
}

void PeriodicResourceGainSpell::new_application_effect() {

}

void PeriodicResourceGainSpell::refresh_effect() {

}

void PeriodicResourceGainSpell::tick_effect() {
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

    add_next_tick();
}

void PeriodicResourceGainSpell::reset_effect() {

}

void PeriodicResourceGainSpell::prepare_set_of_combat_iterations_spell_specific() {
    this->statistics_resource = pchar->get_statistics()->get_resource_statistics(name, icon);
}

bool PeriodicResourceGainSpell::check_application_success() {
    return true;
}
