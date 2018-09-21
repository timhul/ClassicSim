#ifndef IMPROVEDHEROICSTRIKE_H
#define IMPROVEDHEROICSTRIKE_H

#include "Talent.h"

class TalentTree;

class ImprovedHeroicStrike: public Talent {
    Q_OBJECT
public:
    ImprovedHeroicStrike(Character *pchar, TalentTree* tree);
    ~ImprovedHeroicStrike() override;

    void apply_rank_effect() override;
    void remove_rank_effect() override;

private:
};

#endif // IMPROVEDHEROICSTRIKE_H
