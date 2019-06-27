#pragma once

#include "RegeneratingResource.h"

class Character;

class Mana: public RegeneratingResource {
public:
    Mana(Character*);

    void set_base_mana(const unsigned base_mana);
    unsigned get_max_resource() const override;
    unsigned get_resource_per_tick() override;
    ResourceType get_resource_type() const override;
    double get_tick_rate() const override;

    friend class Druid;
    friend class Hunter;
    friend class Mage;
    friend class Paladin;
    friend class Priest;
    friend class Shaman;
    friend class Warlock;

private:
    unsigned base_mana {0};
    unsigned mana_per_tick {0};
    double last_use_of_mana {0.0};
    double remainder {0.0};

    void add_next_tick();

    void reset_effect() override;
    void lose_resource_effect() override;
};
