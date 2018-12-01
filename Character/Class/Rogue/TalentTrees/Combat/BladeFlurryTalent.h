#ifndef BLADEFLURRYTALENT_H
#define BLADEFLURRYTALENT_H

#include "Talent.h"

class BladeFlurry;
class TalentTree;

class BladeFlurryTalent: public Talent {
public:
    BladeFlurryTalent(Character *pchar, TalentTree* tree);

private:
    BladeFlurry* blade_flurry;

    void apply_rank_effect() override;
    void remove_rank_effect() override;
};

#endif // BladeFlurryTALENT_H
