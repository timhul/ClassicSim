#ifndef IMPALE_H
#define IMPALE_H

#include "Talent.h"

class Impale: public Talent {
    Q_OBJECT
public:
    Impale(Character *pchar);
    virtual ~Impale();

private:
};

#endif // IMPALE_H
