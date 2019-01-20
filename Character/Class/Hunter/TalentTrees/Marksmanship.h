#ifndef MARKSMANSHIP_H
#define MARKSMANSHIP_H

#include "TalentTree.h"

class Marksmanship: public TalentTree {
public:
    Marksmanship(Character *pchar);
    ~Marksmanship() override;

private:
};

#endif // MARKSMANSHIP_H
