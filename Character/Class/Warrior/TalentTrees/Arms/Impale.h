#ifndef IMPALE_H
#define IMPALE_H

#include "Talent.h"

class Impale: public Talent {
    Q_OBJECT
public:
    Impale(Character *pchar);
    virtual ~Impale();

    virtual void apply_rank_effect() override;
    virtual void remove_rank_effect() override;

private:
};

#endif // IMPALE_H
