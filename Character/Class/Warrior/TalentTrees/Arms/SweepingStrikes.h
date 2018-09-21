#ifndef SWEEPINGSTRIKES_H
#define SWEEPINGSTRIKES_H

#include "Talent.h"

class TalentTree;

class SweepingStrikes: public Talent {
    Q_OBJECT
public:
    SweepingStrikes(Character *pchar, TalentTree* tree);
    ~SweepingStrikes() override;

    void apply_rank_effect() override;
    void remove_rank_effect() override;

private:
};

#endif // SWEEPINGSTRIKES_H
