#ifndef OPPORTUNITY_H
#define OPPORTUNITY_H

#include "Talent.h"

class Backstab;
class TalentTree;

class Opportunity: public Talent {
public:
    Opportunity(Character *pchar, TalentTree* tree);

private:
    Backstab* backstab;

    void apply_rank_effect() override;
    void remove_rank_effect() override;
};

#endif // OPPORTUNITY_H
