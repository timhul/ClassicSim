#ifndef IMPROVEDPOISONS_H
#define IMPROVEDPOISONS_H

#include "Talent.h"

class InstantPoison;
class TalentTree;

class ImprovedPoisons: public Talent {
public:
    ImprovedPoisons(Character *pchar, TalentTree* tree);

private:
    InstantPoison* mh_instant_poison;
    InstantPoison* oh_instant_poison;

    void apply_rank_effect() override;
    void remove_rank_effect() override;
};

#endif // IMPROVEDPOISONS_H
