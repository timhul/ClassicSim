#ifndef RELENTLESSSTRIKESTALENT_H
#define RELENTLESSSTRIKESTALENT_H

#include "Talent.h"

class RelentlessStrikes;
class TalentTree;

class RelentlessStrikesTalent: public Talent {
public:
    RelentlessStrikesTalent(Character *pchar, TalentTree* tree);

private:
    RelentlessStrikes* RelentlessStrikes;

    void apply_rank_effect() override;
    void remove_rank_effect() override;
};

#endif // RELENTLESSSTRIKESTALENT_H
