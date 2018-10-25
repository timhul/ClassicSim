#ifndef SHAREDBUFF_H
#define SHAREDBUFF_H

#include "Buff.h"

class SharedBuff : public Buff {
public:
    SharedBuff(Character* pchar, const QString& name, const QString& icon, const int duration, const int base_charges);

    bool unused() const;

    void increment_reference();
    void decrement_reference();

protected:
    int reference_counter;

};

#endif // SHAREDBUFF_H
