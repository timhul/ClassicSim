#ifndef FURY_H
#define FURY_H

#include "TalentTree.h"

class Warrior;
class WarriorSpells;

class Fury: public TalentTree {
public:
    Fury(Warrior* pchar);

    Talent* get_unbridled_wrath();
    Talent* get_dual_wield_specialization();

private:
    Warrior* warrior;
    WarriorSpells* spells;
};

#endif // FURY_H
