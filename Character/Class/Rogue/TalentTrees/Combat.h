#ifndef COMBAT_H
#define COMBAT_H

#include "TalentTree.h"

class Combat: public TalentTree {
public:
    Combat(Character *pchar);
    ~Combat() override;

private:
};

#endif // COMBAT_H
