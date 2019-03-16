#ifndef ENERGYTICK_H
#define ENERGYTICK_H

#include "Spell.h"

class Energy;


class EnergyTick : public Spell {
public:
    EnergyTick(Character* pchar, class Energy* energy);

    void perform_periodic() override;

private:
    class Energy* energy;

    void spell_effect() override;
};

#endif // ENERGYTICK_H
