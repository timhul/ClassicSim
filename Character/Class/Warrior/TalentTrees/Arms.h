#ifndef ARMS_H
#define ARMS_H

#include "TalentTree.h"

class Warrior;
class WarriorSpells;

class Arms: public TalentTree {
public:
    Arms(Warrior* pchar);
    ~Arms() override;

    Talent* get_improved_heroic_strike();
    Talent* get_improved_rend();
    Talent* get_improved_overpower();
    Talent* get_deep_wounds();
    Talent* get_mortal_strike();

private:
    Warrior* warr;
    WarriorSpells* spells;
};

#endif // ARMS_H
