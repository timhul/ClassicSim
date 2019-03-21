#include "Buff.h"

#include <utility>

#include "BuffRemoval.h"
#include "Character.h"
#include "ClassStatistics.h"
#include "EnabledBuffs.h"
#include "Engine.h"
#include "StatisticsBuff.h"
#include "Utils/Check.h"

Buff::Buff(Character* pchar, QString  name, QString  icon, const int duration, const int base_charges):
    pchar(pchar),
    statistics_buff(nullptr),
    name(std::move(name)),
    icon(std::move(icon)),
    duration(duration),
    base_charges(base_charges),
    enabled(false),
    hidden(false),
    debuff(false),
    instance_id(BuffStatus::INACTIVE)
{
    initialize();
}

QString Buff::get_name() const {
    return this->name;
}

QString Buff::get_icon() const {
    return this->icon;
}

int Buff::get_charges() const {
    return this->current_charges;
}

void Buff::apply_buff() {
    if (!is_enabled())
        return;

    this->current_charges = base_charges;

    if (!is_active()) {
        this->applied = pchar->get_engine()->get_current_priority();
        this->buff_effect_when_applied();
    }
    else
        this->buff_effect_when_refreshed();

    this->refreshed = pchar->get_engine()->get_current_priority();
    this->active = true;
    if (this->duration != BuffDuration::PERMANENT) {
        auto* new_event = new BuffRemoval(this,
                                          pchar->get_engine()->get_current_priority() + duration,
                                          ++iteration);
        pchar->get_engine()->add_event(new_event);
    }
}

void Buff::refresh_buff() {
    if (!is_enabled())
        return;

    if (!is_active())
        return;

    this->refreshed = pchar->get_engine()->get_current_priority();
    this->buff_effect_when_refreshed();
}

void Buff::remove_buff(const int iteration) {
    if (iteration != this->iteration || !is_active())
        return;

    force_remove_buff();
}

void Buff::force_remove_buff() {
    this->expired = pchar->get_engine()->get_current_priority();
    this->active = false;
    this->uptime += expired - applied;

    if (!hidden)
        this->statistics_buff->add_uptime(expired - applied);

    this->buff_effect_when_removed();
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

    return this->refreshed + this->duration - pchar->get_engine()->get_current_priority();
}

void Buff::reset() {
    if (is_active())
        force_remove_buff();

    if (!is_hidden())
        statistics_buff->add_uptime_for_encounter(uptime / pchar->get_sim_settings()->get_combat_length());

    initialize();
    reset_effect();
}

void Buff::initialize() {
    current_charges = 0;
    iteration = 0;
    applied = duration - 1;
    refreshed = duration - 1;
    expired = duration - 1;
    active = false;
    uptime = 0;
}

bool Buff::is_enabled() const {
    return enabled;
}

bool Buff::is_hidden() const {
    return hidden;
}

bool Buff::is_debuff() const {
    return debuff;
}

void Buff::set_instance_id(const int instance_id) {
    this->instance_id = instance_id;
}

int Buff::get_instance_id() const {
    return this->instance_id;
}

void Buff::enable_buff() {
    check(!enabled, QString("Tried to enable an already enabled buff '%1'").arg(name).toStdString());

    this->enabled = true;
    pchar->get_enabled_buffs()->add_buff(this);
}

void Buff::disable_buff() {
    check(enabled, QString("Tried to disabled an already disabled buff '%1'").arg(name).toStdString());

    pchar->get_enabled_buffs()->remove_buff(this);
    this->enabled = false;
}

void Buff::prepare_set_of_combat_iterations() {
    initialize();

    if (this->is_hidden())
        return;

    this->statistics_buff = pchar->get_statistics()->get_buff_statistics(name, icon, debuff);
}

void Buff::buff_effect_when_refreshed() {

}

void Buff::reset_effect() {

}

void Buff::charge_change_effect() {

}
