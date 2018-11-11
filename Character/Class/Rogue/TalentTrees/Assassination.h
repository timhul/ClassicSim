#ifndef ASSASSINATION_H
#define ASSASSINATION_H

#include "TalentTree.h"

class Assassination: public TalentTree {
public:
    Assassination(Character *pchar);
    ~Assassination() override;

private:
};

#endif // ASSASSINATION_H
