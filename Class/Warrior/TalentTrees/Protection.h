#pragma once

#include "TalentTree.h"

class Warrior;

class Protection: public TalentTree {
public:
    Protection(Warrior *pchar);

    Talent* get_improved_shield_block();

private:
    Warrior* warrior;
};
