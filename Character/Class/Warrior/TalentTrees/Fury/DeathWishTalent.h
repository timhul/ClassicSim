#ifndef DEATHWISHTALENT_H
#define DEATHWISHTALENT_H

#include "Talent.h"

class DeathWish;
class DeathWishBuff;
class TalentTree;

class DeathWishTalent: public Talent {
    Q_OBJECT
public:
    DeathWishTalent(Character *pchar, TalentTree* tree);
    ~DeathWishTalent() override;

private:
    DeathWish* death_wish;
    DeathWishBuff* death_wish_buff;

    void apply_rank_effect() override;
    void remove_rank_effect() override;
};

#endif // DEATHWISHTALENT_H
