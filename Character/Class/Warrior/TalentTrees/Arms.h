#ifndef ARMS_H
#define ARMS_H

#include "TalentTree.h"

class Arms: public TalentTree {
public:
    Arms(Character* pchar);
    ~Arms() override;

private:
};

#endif // ARMS_H
