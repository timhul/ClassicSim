
#include "SharedBuff.h"

SharedBuff::SharedBuff(Character* pchar,
                       const QString& name,
                       const int duration,
                       const int base_charges) :
    Buff(pchar, name, duration, base_charges),
    reference_counter(0)
{}

bool SharedBuff::unused() const {
    return reference_counter < 1;
}

void SharedBuff::increment_reference() {
    ++reference_counter;
}

void SharedBuff::decrement_reference() {
    --reference_counter;
}
