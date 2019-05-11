#ifndef MANAPOTION_H
#define MANAPOTION_H

#include "Spell.h"

class Random;
class StatisticsResource;

class ManaPotion: public Spell {
public:
    ManaPotion(Character* pchar);
    ~ManaPotion() override;

private:
    const unsigned min {1350};
    const unsigned max {2251};
    Random* random;
    StatisticsResource* statistics_resource {nullptr};

    void spell_effect() override;
    SpellStatus is_ready_spell_specific() const override;
    void prepare_set_of_combat_iterations_spell_specific() override;
};

#endif // MANAPOTION_H
