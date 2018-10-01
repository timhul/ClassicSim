
#include "Buff.h"
#include "ActiveBuffs.h"
#include "Character.h"
#include "ClassStatistics.h"
#include "StatisticsBuff.h"
#include "Engine.h"
#include "BuffRemoval.h"
#include <QDebug>

Buff::Buff(Character* pchar, const QString& name, const int duration, const int base_charges):
    pchar(pchar),
    statistics_buff(new StatisticsBuff(name)),
    name(name),
    duration(duration),
    base_charges(base_charges),
    rank_talent(1),
    hidden(false),
    instance_id(BuffStatus::INACTIVE)
{
    initialize();
}

Buff::~Buff() {
    delete statistics_buff;
}

StatisticsBuff* Buff::get_statistics_for_buff() const {
    return this->statistics_buff;
}

QString Buff::get_name() const {
    return this->name;
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

    this->refreshed = pchar->get_engine()->get_current_priority();
    this->active = true;

    if (this->duration != BuffDuration::PERMANENT) {
        auto* new_event = new BuffRemoval(this,
                                          pchar->get_engine()->get_current_priority() + duration,
                                          ++iteration);
        pchar->get_engine()->add_event(new_event);
    }
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

    this->buff_effect_when_removed();
}

void Buff::use_charge() {
    if (!is_active())
        return;

    assert(this->current_charges > 0);

    if (--this->current_charges == 0)
        force_remove_buff();
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

    // TODO: Remove knowledge of fight length being 300s.
    statistics_buff->add_uptime_for_encounter(uptime / 300);
    initialize();
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
    return rank_talent > 0;
}

bool Buff::is_hidden() const {
    return hidden;
}

void Buff::increase_rank() {
    ++rank_talent;
    // TODO: Assert max rank?
}

void Buff::decrease_rank() {
    --rank_talent;
    assert(rank_talent >= 0);
}

void Buff::set_instance_id(const int instance_id) {
    this->instance_id = instance_id;
}

int Buff::get_instance_id() const {
    return this->instance_id;
}

void Buff::add_buff_statistic() {
    if (this->is_hidden())
        return;

    pchar->get_statistics()->add_buff_statistics(this->statistics_buff);
}

void Buff::remove_buff_statistic() {
    if (this->is_hidden())
        return;

    pchar->get_statistics()->remove_buff_statistics(this->statistics_buff->get_name());
}

void Buff::enable_buff() {
    this->add_buff_statistic();
    pchar->get_active_buffs()->add_buff(this);
}

void Buff::disable_buff() {
    this->remove_buff_statistic();
    pchar->get_active_buffs()->remove_buff(this);
}
