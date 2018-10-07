#ifndef FLURRYTALENT_H
#define FLURRYTALENT_H

#include "Talent.h"

class TalentTree;

class FlurryTalent: public Talent {
    Q_OBJECT
public:
    FlurryTalent(Character *pchar, TalentTree* tree);
    ~FlurryTalent() override;

private:
    void apply_rank_effect() override;
    void remove_rank_effect() override;
};

#endif // FLURRYTALENT_H
