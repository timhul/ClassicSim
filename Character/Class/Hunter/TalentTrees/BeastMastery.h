#ifndef BEASTMASTERY_H
#define BEASTMASTERY_H

#include "TalentTree.h"

class BeastMastery: public TalentTree {
public:
    BeastMastery(Character *pchar);
    ~BeastMastery() override;

private:
};

#endif // BEASTMASTERY_H
