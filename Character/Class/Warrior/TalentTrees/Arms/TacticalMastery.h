#ifndef TACTICALMASTERY_H
#define TACTICALMASTERY_H

#include "Talent.h"

class TalentTree;
class Warrior;

class TacticalMastery: public Talent {
    Q_OBJECT
public:
    TacticalMastery(Character *pchar, TalentTree* tree);
    ~TacticalMastery() override;

    void apply_rank_effect() override;
    void remove_rank_effect() override;

private:
    Warrior* warr;
};

#endif // TACTICALMASTERY_H
