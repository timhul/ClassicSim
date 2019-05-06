#ifndef HAMSTRING_H
#define HAMSTRING_H

#include "ItemModificationRequirer.h"
#include "Spell.h"

class Warrior;
class WarriorSpells;

class Hamstring: public Spell, public ItemModificationRequirer {
public:
    Hamstring(Warrior* pchar, WarriorSpells* spells);

private:
    Warrior* warr;
    WarriorSpells* spells;

    void spell_effect() override;

    void activate_item_effect(const int item_id) override;
    void deactivate_item_effect(const int item_id) override;
};

#endif // HAMSTRING_H
