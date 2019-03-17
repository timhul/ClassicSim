#ifndef MULTISHOT_H
#define MULTISHOT_H

#include "Spell.h"

class MultiShot: public Spell {
public:
    MultiShot(Character* pchar);

private:
    QVector<double> talent_ranks;

    virtual void spell_effect() override;
};

#endif // MULTISHOT_H
