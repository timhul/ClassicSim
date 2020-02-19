#include "Buff.h"

#include <utility>

#include "BuffRemoval.h"
#include "Character.h"
#include "ClassStatistics.h"
#include "EnabledBuffs.h"
#include "Engine.h"
#include "RaidControl.h"
#include "StatisticsBuff.h"
#include "Target.h"
#include "Utils/Check.h"

Buff::Buff(Character* pchar, QString name, QString icon, const int duration, const int base_charges) :
    name(std::move(name)),
    icon(std::move(icon)),
    pchar(pchar),
    raid_control(pchar->get_raid_control()),
    duration(duration),
    base_charges(base_charges),
    enabled(false),
    hidden(false),
    affected(Affected::Self),
    instance_id(InstanceID::INACTIVE) {
    initialize();
}

int Buff::get_charges() const {
    return this->current_charges;
}

int Buff::get_stacks() const {
    return this->current_stacks;
}

void Buff::apply_buff() {
    if (!is_enabled())
        return;

    if (!is_active()) {
        if (!apply_buff_to_target())
            return;

        this->current_stacks = 1;
        this->applied = raid_control->get_engine()->get_current_priority();
    } else {
        if (current_stacks < max_stacks)
            ++current_stacks;

        this->buff_effect_when_refreshed();
    }

    this->current_charges = base_charges;
    this->refreshed = raid_control->get_engine()->get_current_priority();
    this->active = true;
    if (this->duration != BuffDuration::PERMANENT) {
        auto new_event = new BuffRemoval(this, raid_control->get_engine()->get_current_priority() + duration, ++iteration);
        raid_control->get_engine()->add_event(new_event);
    }
}

void Buff::refresh_buff() {
    if (!is_enabled())
        return;

    if (!is_active())
        return;

    if (current_stacks < max_stacks)
        ++current_stacks;

    this->refreshed = raid_control->get_engine()->get_current_priority();
    this->buff_effect_when_refreshed();
}

void Buff::remove_buff(const int iteration) {
    if (iteration != this->iteration || !is_active())
        return;

    force_remove_buff();
}

void Buff::force_remove_buff() {
    if (is_active())
        remove_buff_from_target();

    this->expired = raid_control->get_engine()->get_current_priority();
    this->active = false;
    this->current_stacks = 0;

    this->uptime += expired - applied;

    if (!hidden)
        this->statistics_buff->add_uptime(expired - applied);
}

void Buff::use_charge() {
    if (!is_active())
        return;

    check((this->current_charges > 0), "Attempted to use charge but has no charges");

    if (--this->current_charges == 0)
        force_remove_buff();
    else
        charge_change_effect();
}

void Buff::cancel_buff() {
    if (!is_active())
        return;

    force_remove_buff();
}

bool Buff::is_active() const {
    return this->active;
}

double Buff::time_left() const {
    if (!is_active())
        return 0;

    if (duration == BuffDuration::PERMANENT)
        return std::numeric_limits<double>::max();

    return this->refreshed + this->duration - raid_control->get_engine()->get_current_priority();
}

double Buff::get_expired() const {
    return this->expired;
}

void Buff::reset() {
    if (is_active())
        force_remove_buff();

    if (!is_hidden())
        statistics_buff->add_uptime_for_encounter(uptime / raid_control->get_sim_settings()->get_combat_length());

    initialize();
    reset_effect();
}

void Buff::initialize() {
    current_charges = 0;
    current_stacks = 0;
    iteration = 0;
    applied = 0;
    refreshed = 0;
    expired = 0;
    uptime = 0;
    active = false;
}

bool Buff::is_enabled() const {
    return enabled;
}

bool Buff::is_hidden() const {
    return hidden;
}

bool Buff::is_debuff() const {
    return affected == Affected::Target;
}

void Buff::set_instance_id(const int instance_id) {
    this->instance_id = instance_id;
}

int Buff::get_instance_id() const {
    return this->instance_id;
}

void Buff::buff_effect_when_refreshed() {}

void Buff::reset_effect() {}

void Buff::charge_change_effect() {}

void Buff::prepare_set_of_combat_iterations_spell_specific() {}
