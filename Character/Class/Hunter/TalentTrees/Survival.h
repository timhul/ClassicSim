#ifndef SURVIVAL_H
#define SURVIVAL_H

#include "TalentTree.h"

class Survival: public TalentTree {
public:
    Survival(Character *pchar);
    ~Survival() override;

private:
};

#endif // SURVIVAL_H
