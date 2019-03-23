#ifndef MANA_H
#define MANA_H

#include "Resource.h"

class Character;
class ManaTick;

class Mana: public Resource {
public:
    Mana(Character*);
    ~Mana() override;

    void gain_resource(const unsigned) override;
    void lose_resource(const unsigned) override;
    void reset_resource() override;

    void set_base_mana(const unsigned base_mana);
    unsigned get_max_mana() const;
    void tick_mana();

    friend class Druid;
    friend class Hunter;
    friend class Mage;
    friend class Paladin;
    friend class Priest;
    friend class Shaman;
    friend class Warlock;

private:
    Character* pchar;
    ManaTick* mana_tick;
    unsigned base_mana;
    unsigned mana_per_tick;

    void add_next_tick();
};

#endif // MANA_H
