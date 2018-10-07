#ifndef HAMSTRING_H
#define HAMSTRING_H

#include "Spell.h"

class Warrior;

class Hamstring: public Spell {
public:
    Hamstring(Character* pchar);

protected:
private:
    Warrior* warr;

    void spell_effect() override;
};

#endif // HAMSTRING_H
