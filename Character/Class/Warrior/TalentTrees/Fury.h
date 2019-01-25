#ifndef FURY_H
#define FURY_H

#include "TalentTree.h"

class Warrior;
class WarriorSpells;

class Fury: public TalentTree {
public:
    Fury(Character *pchar);
    ~Fury() override;

private:
    Warrior* warr;
    WarriorSpells* spells;
};

#endif // FURY_H
