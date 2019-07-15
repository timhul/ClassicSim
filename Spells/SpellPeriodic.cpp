#include "SpellPeriodic.h"

#include "Buff.h"
#include "Character.h"
#include "CooldownControl.h"
#include "DotTick.h"
#include "Engine.h"
#include "SharedDebuff.h"
#include "Utils/CompareDouble.h"

SpellPeriodic::SpellPeriodic(const QString& name,
                             const QString& icon,
                             Character* pchar,
                             Buff* marker_buff,
                             const RestrictedByGcd restricted_by_gcd,
                             const ResourceType resource_type,
                             const double tick_rate,
                             unsigned resource_cost,
                             int spell_rank) :
    Spell(name, icon, pchar, new CooldownControl(pchar, 0.0), restricted_by_gcd, resource_type, resource_cost, spell_rank),
    marker_buff(marker_buff),
    tick_rate(tick_rate)
{
    enabled = false;
}

SpellPeriodic::~SpellPeriodic() {
    delete cooldown;
}

void SpellPeriodic::perform_periodic(const int application_id) {
    if (!is_enabled())
        return;

    if (!marker_buff->is_active() && !almost_equal(marker_buff->get_expired(), pchar->get_engine()->get_current_priority()))
        return reset_effect();

    if (this->application_id != application_id)
        return;

    tick_effect();
}

bool SpellPeriodic::is_active() const {
    return marker_buff->is_active();
}

void SpellPeriodic::invalidate() {
    marker_buff->cancel_buff();
}

void SpellPeriodic::spell_effect() {
    if (!is_enabled())
        return;

    if (!check_application_success())
        return;

    if (marker_buff->is_active())
        return refresh_effect();

    marker_buff->apply_buff();
    if (!marker_buff->is_active())
        return;

    start_ticking();

    new_application_effect();
}

void SpellPeriodic::enable_spell_effect() {
    if (dynamic_cast<SharedDebuff*>(marker_buff))
        return;

    marker_buff->enable_buff();
}

void SpellPeriodic::disable_spell_effect() {
    if (dynamic_cast<SharedDebuff*>(marker_buff))
        return;

    marker_buff->disable_buff();
}

void SpellPeriodic::add_next_tick() {
    pchar->get_engine()->add_event(new DotTick(this, pchar->get_engine()->get_current_priority() + tick_rate, application_id));
}

void SpellPeriodic::start_ticking() {
    pchar->get_engine()->add_event(new DotTick(this, pchar->get_engine()->get_current_priority() + tick_rate, ++application_id));
}
