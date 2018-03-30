#ifndef TACTICALMASTERY_H
#define TACTICALMASTERY_H

#include "Talent.h"

class TalentTree;

class TacticalMastery: public Talent {
    Q_OBJECT
public:
    TacticalMastery(Character *pchar, TalentTree* tree);
    virtual ~TacticalMastery();

    virtual void apply_rank_effect() override;
    virtual void remove_rank_effect() override;

private:
};

#endif // TACTICALMASTERY_H
