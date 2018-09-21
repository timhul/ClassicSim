#ifndef IMPROVEDCLEAVE_H
#define IMPROVEDCLEAVE_H

#include "Talent.h"

class TalentTree;

class ImprovedCleave: public Talent {
    Q_OBJECT
public:
    ImprovedCleave(Character *pchar, TalentTree* tree);
    ~ImprovedCleave() override;

    void apply_rank_effect() override;
    void remove_rank_effect() override;

private:
};

#endif // IMPROVEDCLEAVE_H
