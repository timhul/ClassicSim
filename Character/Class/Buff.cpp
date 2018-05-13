
#include "Buff.h"
#include "Character.h"
#include "StatisticsBuff.h"
#include "Engine.h"
#include "BuffRemoval.h"
#include <QDebug>

Buff::Buff(Character* _pchar, const QString _name, const int _dur, const int _base_charges):
    pchar(_pchar),
    statistics(new StatisticsBuff(_name)),
    name(_name),
    duration(_dur),
    base_charges(_base_charges),
    rank_talent(1),
    hidden(false)
{
    initialize();
}

Buff::~Buff() {
    delete statistics;
}

StatisticsBuff* Buff::get_statistics_for_buff() const {
    return this->statistics;
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
    // TODO: Decide if we should use BuffApplication event as well.
    BuffRemoval* new_event = new BuffRemoval(this, pchar->get_engine()->get_current_priority() + duration, ++iteration);
    pchar->get_engine()->add_event(new_event);
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

bool Buff::is_active() const {
    return this->active;
}

float Buff::time_left() const {
    if (!is_active())
        return 0;
    return this->refreshed + this->duration - pchar->get_engine()->get_current_priority();
}

void Buff::reset() {
    if (is_active())
        force_remove_buff();

    // TODO: Remove knowledge of fight length being 300s.
    statistics->add_uptime_for_encounter(uptime / 300);
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
