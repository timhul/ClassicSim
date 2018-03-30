#ifndef DEATHWISH_H
#define DEATHWISH_H

#include "Talent.h"

class TalentTree;

class DeathWish: public Talent {
    Q_OBJECT
public:
    DeathWish(Character *pchar, TalentTree* tree);
    virtual ~DeathWish();

    virtual void apply_rank_effect() override;
    virtual void remove_rank_effect() override;

private:
};

#endif // DEATHWISH_H
