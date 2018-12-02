#ifndef IMPROVEDSINISTERSTRIKE_H
#define IMPROVEDSINISTERSTRIKE_H

#include "Talent.h"

class SinisterStrike;
class TalentTree;

class ImprovedSinisterStrike: public Talent {
public:
    ImprovedSinisterStrike(Character *pchar, TalentTree* tree);

private:
    SinisterStrike* sinister_strike;

    void apply_rank_effect() override;
    void remove_rank_effect() override;
};

#endif // IMPROVEDSINISTERSTRIKE_H
