#ifndef OVERPOWER_H
#define OVERPOWER_H

#include "Spell.h"

class Warrior;

class Overpower: public Spell {
public:
    Overpower(Character* pchar);

protected:
private:
    Warrior* warr;
    QVector<double> talent_ranks;

    bool is_ready_spell_specific() const override;
    void spell_effect() override;
};

#endif // OVERPOWER_H
