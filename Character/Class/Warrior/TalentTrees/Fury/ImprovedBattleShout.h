#ifndef IMPROVEDBATTLESHOUT_H
#define IMPROVEDBATTLESHOUT_H

#include "Talent.h"

class BattleShoutBuff;
class TalentTree;

class ImprovedBattleShout: public Talent {
public:
    ImprovedBattleShout(Character *pchar, TalentTree* tree);
    ~ImprovedBattleShout() override;

private:
    BattleShoutBuff* battle_shout_buff;

    void apply_rank_effect() override;
    void remove_rank_effect() override;
};

#endif // IMPROVEDBATTLESHOUT_H
