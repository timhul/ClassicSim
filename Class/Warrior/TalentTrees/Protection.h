#ifndef PROTECTION_H
#define PROTECTION_H

#include "TalentTree.h"

class Warrior;

class Protection: public TalentTree {
public:
    Protection(Warrior *pchar);

    Talent* get_improved_shield_block();
private:
    Warrior* warrior;
};

#endif // PROTECTION_H
