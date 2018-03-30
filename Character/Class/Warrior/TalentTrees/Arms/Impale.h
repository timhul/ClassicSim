#ifndef IMPALE_H
#define IMPALE_H

#include "Talent.h"

class TalentTree;

class Impale: public Talent {
    Q_OBJECT
public:
    Impale(Character *pchar, TalentTree* tree);
    virtual ~Impale();

    virtual void apply_rank_effect() override;
    virtual void remove_rank_effect() override;

private:
};

#endif // IMPALE_H
