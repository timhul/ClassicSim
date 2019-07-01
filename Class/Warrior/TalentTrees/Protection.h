#pragma once

#include "TalentTree.h"

class Warrior;

class Protection: public TalentTree {
public:
    Protection(Warrior *pchar);

private:
    Warrior* warrior;

    void add_improved_shield_block(QMap<QString, Talent*>& talent_tier);
};
