#pragma once

#include "ItemModificationRequirer.h"
#include "Spell.h"

class Random;
class StatisticsResource;

class RobeOfTheArchmage : public Spell, public ItemModificationRequirer {
public:
    RobeOfTheArchmage(Character* pchar);
    ~RobeOfTheArchmage() override;

private:
    const unsigned min {375};
    const unsigned max {626};
    Random* random;
    StatisticsResource* statistics_resource {nullptr};

    void spell_effect() override;
    SpellStatus is_ready_spell_specific() const override;
    void prepare_set_of_combat_iterations_spell_specific() override;

    void activate_item_effect(const int item_id) override;
    void deactivate_item_effect(const int item_id) override;
};
