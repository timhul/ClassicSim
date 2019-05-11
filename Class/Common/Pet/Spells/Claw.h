#ifndef CLAW_H
#define CLAW_H

#include "Spell.h"

class Pet;
class Random;

class Claw: public Spell {
public:
    Claw(Character* pchar, Pet *pet);
    ~Claw() override;

private:
    Pet* pet;
    Random* dmg_roll;

    void spell_effect() override;
};

#endif // CLAW_H
