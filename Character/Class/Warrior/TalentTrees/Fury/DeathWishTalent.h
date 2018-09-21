#ifndef DEATHWISHTALENT_H
#define DEATHWISHTALENT_H

#include "Talent.h"

class TalentTree;

class DeathWishTalent: public Talent {
    Q_OBJECT
public:
    DeathWishTalent(Character *pchar, TalentTree* tree);
    ~DeathWishTalent() override;

    void apply_rank_effect() override;
    void remove_rank_effect() override;

private:
};

#endif // DEATHWISHTALENT_H
