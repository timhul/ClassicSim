#ifndef IMPROVEDCLEAVE_H
#define IMPROVEDCLEAVE_H

#include "Talent.h"

class TalentTree;

class ImprovedCleave: public Talent {
    Q_OBJECT
public:
    ImprovedCleave(Character *pchar, TalentTree* tree);
    virtual ~ImprovedCleave();

    virtual void apply_rank_effect() override;
    virtual void remove_rank_effect() override;

private:
};

#endif // IMPROVEDCLEAVE_H
