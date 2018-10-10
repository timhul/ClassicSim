#ifndef IMPROVEDHEROICSTRIKE_H
#define IMPROVEDHEROICSTRIKE_H

#include "Talent.h"

class HeroicStrike;
class TalentTree;

class ImprovedHeroicStrike: public Talent {
    Q_OBJECT
public:
    ImprovedHeroicStrike(Character *pchar, TalentTree* tree);
    ~ImprovedHeroicStrike() override;

private:
    HeroicStrike* heroic_strike;

    void apply_rank_effect() override;
    void remove_rank_effect() override;
};

#endif // IMPROVEDHEROICSTRIKE_H
