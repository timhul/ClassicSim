#ifndef IMPROVEDCLEAVE_H
#define IMPROVEDCLEAVE_H

#include "Talent.h"

class TalentTree;

class ImprovedCleave: public Talent {
public:
    ImprovedCleave(Character *pchar, TalentTree* tree);
    ~ImprovedCleave() override;

private:
    void apply_rank_effect() override;
    void remove_rank_effect() override;
};

#endif // IMPROVEDCLEAVE_H
