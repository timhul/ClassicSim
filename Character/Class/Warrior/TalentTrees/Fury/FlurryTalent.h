#ifndef FLURRYTALENT_H
#define FLURRYTALENT_H

#include "Talent.h"

class TalentTree;

class FlurryTalent: public Talent {
    Q_OBJECT
public:
    FlurryTalent(Character *pchar, TalentTree* tree);
    virtual ~FlurryTalent();

    virtual void apply_rank_effect() override;
    virtual void remove_rank_effect() override;

private:
};

#endif // FLURRYTALENT_H
