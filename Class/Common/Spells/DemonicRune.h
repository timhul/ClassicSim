#ifndef DEMONICRUNE_H
#define DEMONICRUNE_H

#include "Spell.h"

class Random;
class StatisticsResource;

class DemonicRune: public Spell {
public:
    DemonicRune(Character* pchar);
    ~DemonicRune() override;

private:
    const unsigned min {900};
    const unsigned max {1501};
    Random* random;
    StatisticsResource* statistics_resource {nullptr};

    void spell_effect() override;
    SpellStatus is_ready_spell_specific() const override;
    void prepare_set_of_combat_iterations_spell_specific() override;
};

#endif // DEMONICRUNE_H
