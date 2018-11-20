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

    void add_next_tick();
    unsigned mana_per_tick;
};

#endif // MANA_H
