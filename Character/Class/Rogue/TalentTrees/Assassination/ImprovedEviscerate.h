#ifndef IMPROVEDEVISCERATE_H
#define IMPROVEDEVISCERATE_H

#include "Talent.h"

class Eviscerate;
class TalentTree;

class ImprovedEviscerate: public Talent {
public:
    ImprovedEviscerate(Character *pchar, TalentTree* tree);

private:
    Eviscerate* eviscerate;

    void apply_rank_effect() override;
    void remove_rank_effect() override;
};

#endif // IMPROVEDEVISCERATE_H
