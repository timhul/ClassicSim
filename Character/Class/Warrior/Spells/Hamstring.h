#ifndef HAMSTRING_H
#define HAMSTRING_H

#include "ItemModificationRequirer.h"
#include "Spell.h"

class Warrior;

class Hamstring: public Spell, public ItemModificationRequirer {
public:
    Hamstring(Character* pchar);

private:
    Warrior* warr;

    void spell_effect() override;

    void activate_item_effect(const int item_id) override;
    void deactivate_item_effect(const int item_id) override;
};

#endif // HAMSTRING_H
