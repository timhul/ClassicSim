#ifndef CRUELTY_H
#define CRUELTY_H

#include "Talent.h"

class Cruelty: public Talent {
    Q_OBJECT
public:
    Cruelty(Character *pchar);
    virtual ~Cruelty();

    virtual void apply_rank_effect() override;
    virtual void remove_rank_effect() override;

private:
};

#endif // CRUELTY_H
