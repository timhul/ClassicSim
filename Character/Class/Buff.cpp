
#include "Buff.h"

std::string Buff::get_name() const {
    return this->name;
}

void Buff::apply_buff(const float timestamp, const int charges) {
    this->charges = charges;

    if (!is_active())
        this->applied = timestamp;

    this->refreshed = timestamp;
    this->active = true;
}

void Buff::remove_buff(const float timestamp) {
    this->expired = timestamp;
    this->active = false;
}

void Buff::use_charge(const float timestamp) {
    assert(this->charges > 0);

    if (--this->charges == 0)
        remove_buff(timestamp);
}

bool Buff::is_active() const {
    return this->active;
}

float Buff::time_left(const float timestamp) const {
    if (!is_active())
        return 0;
    return this->refreshed + this->duration - timestamp;
}
