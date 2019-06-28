#pragma once

#include "SelfBuff.h"

class SharedBuff : public SelfBuff {
public:
    SharedBuff(Character* pchar, const QString& name, const QString& icon, const int duration, const int base_charges);

    bool unused() const;

    void increment_reference();
    void decrement_reference();

protected:
    int reference_counter;
};
