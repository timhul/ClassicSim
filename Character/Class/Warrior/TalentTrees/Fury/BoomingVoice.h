#ifndef BOOMINGVOICE_H
#define BOOMINGVOICE_H

#include "Talent.h"

class BattleShoutBuff;
class TalentTree;

class BoomingVoice: public Talent {
    Q_OBJECT
public:
    BoomingVoice(Character *pchar, TalentTree* tree);
    ~BoomingVoice() override;

private:
    BattleShoutBuff* battle_shout_buff;

    void apply_rank_effect() override;
    void remove_rank_effect() override;
};

#endif // BOOMINGVOICE_H
