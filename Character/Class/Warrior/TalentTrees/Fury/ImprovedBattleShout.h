#ifndef IMPROVEDBATTLESHOUT_H
#define IMPROVEDBATTLESHOUT_H

#include "Talent.h"

class TalentTree;

class ImprovedBattleShout: public Talent {
    Q_OBJECT
public:
    ImprovedBattleShout(Character *pchar, TalentTree* tree);
    ~ImprovedBattleShout() override;

private:
    void apply_rank_effect() override;
    void remove_rank_effect() override;
};

#endif // IMPROVEDBATTLESHOUT_H
