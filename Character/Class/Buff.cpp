
#include "Buff.h"
#include "Character.h"
#include "Engine.h"
#include "BuffRemoval.h"

Buff::Buff(Character* _pchar, const QString _name, const int _dur, const int _base_charges):
    pchar(_pchar),
    name(_name),
    duration(_dur),
    base_charges(_base_charges),
    current_charges(_base_charges),
    iteration(0),
    applied(_dur - 1),
    refreshed(_dur - 1),
    expired(_dur - 1),
    active(false)
{}

Buff::~Buff() {
}

QString Buff::get_name() const {
    return this->name;
}

void Buff::apply_buff() {
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
    if (iteration != this->iteration)
        return;

    force_remove_buff();
}

void Buff::force_remove_buff() {
    this->expired = pchar->get_engine()->get_current_priority();
    this->active = false;
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
