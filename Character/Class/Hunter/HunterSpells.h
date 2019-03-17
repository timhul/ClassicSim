#ifndef HUNTERSPELLS_H
#define HUNTERSPELLS_H

#include "CharacterSpells.h"

class Hunter;

class HunterSpells: public CharacterSpells {
public:
    HunterSpells(Hunter *hunter);

    void add_next_ranged_attack() override;

    AutoShoot* get_auto_shoot() const override;

private:
    Hunter* hunter;
    AutoShoot* auto_shoot;
};

#endif // HUNTERSPELLS_H
