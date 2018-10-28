#ifndef FLURRYTALENT_H
#define FLURRYTALENT_H

#include "Talent.h"

class Flurry;
class TalentTree;

class FlurryTalent: public Talent {
public:
    FlurryTalent(Character *pchar, TalentTree* tree);
    ~FlurryTalent() override;

private:
    Flurry* flurry;

    void apply_rank_effect() override;
    void remove_rank_effect() override;
};

#endif // FLURRYTALENT_H
