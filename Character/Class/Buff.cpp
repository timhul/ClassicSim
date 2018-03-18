
#include "Buff.h"
#include "Character.h"
#include "Engine.h"

Buff::Buff(Character* _pchar, const std::string _name, const int _dur):
    pchar(_pchar),
    name(_name),
    duration(_dur),
    applied(_dur - 1),
    refreshed(_dur - 1),
    expired(_dur - 1),
    base_charges(0),
    current_charges(base_charges),
    active(false)
{}

std::string Buff::get_name() const {
    return this->name;
}

void Buff::apply_buff() {
    this->current_charges = base_charges;

    if (!is_active())
        this->applied = pchar->get_engine()->get_current_priority();

    this->refreshed = pchar->get_engine()->get_current_priority();
    this->active = true;
    this->buff_effect_when_applied();
}

void Buff::remove_buff() {
    this->expired = pchar->get_engine()->get_current_priority();
    this->active = false;
    this->buff_effect_when_removed();
}

void Buff::use_charge() {
    assert(this->current_charges > 0);

    if (--this->current_charges == 0)
        remove_buff();
}

bool Buff::is_active() const {
    return this->active;
}

float Buff::time_left() const {
    if (!is_active())
        return 0;
    return this->refreshed + this->duration - pchar->get_engine()->get_current_priority();
}
