#ifndef AGGRESSION_H
#define AGGRESSION_H

#include "Talent.h"

class Eviscerate;
class SinisterStrike;
class TalentTree;

class Aggression: public Talent {
public:
    Aggression(Character *pchar, TalentTree* tree);

private:
    Eviscerate* eviscerate;
    SinisterStrike* sinister_strike;

    void apply_rank_effect() override;
    void remove_rank_effect() override;
};

#endif // AGGRESSION_H
