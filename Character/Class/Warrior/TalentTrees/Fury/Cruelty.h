#ifndef CRUELTY_H
#define CRUELTY_H

#include "Talent.h"

class Cruelty: public Talent {
    Q_OBJECT
public:
    Cruelty(Character *pchar);
    virtual ~Cruelty();

private:
};

#endif // CRUELTY_H
