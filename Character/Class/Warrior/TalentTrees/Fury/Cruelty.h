#ifndef CRUELTY_H
#define CRUELTY_H

#include "Talent.h"

class TalentTree;

class Cruelty: public Talent {
    Q_OBJECT
public:
    Cruelty(Character *pchar, TalentTree* tree);
    virtual ~Cruelty();

    virtual void apply_rank_effect() override;
    virtual void remove_rank_effect() override;

private:
};

#endif // CRUELTY_H
