#ifndef ENERGY_H
#define ENERGY_H

#include "Resource.h"

class Character;
class EnergyTick;

class Energy: public Resource {
public:
    Energy(Character*);
    ~Energy() override;

    void gain_resource(const unsigned) override;
    void lose_resource(const unsigned) override;
    void reset_resource() override;

    void tick_energy();
    void increase_energy_per_tick();
    void decrease_energy_per_tick();

    friend class Druid;
    friend class Rogue;

private:
    Character* pchar;
    EnergyTick* energy_tick;

    void add_next_tick();
    unsigned energy_per_tick;
};

#endif // ENERGY_H
