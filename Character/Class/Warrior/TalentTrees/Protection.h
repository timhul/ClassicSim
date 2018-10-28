#ifndef PROTECTION_H
#define PROTECTION_H

#include "TalentTree.h"

class Protection: public TalentTree {
public:
    Protection(Character *pchar);
    ~Protection() override;

private:
};

#endif // PROTECTION_H
