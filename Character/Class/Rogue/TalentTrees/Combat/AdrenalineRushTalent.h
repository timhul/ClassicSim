#ifndef ADRENALINERUSHTALENT_H
#define ADRENALINERUSHTALENT_H

#include "Talent.h"

class AdrenalineRush;
class TalentTree;

class AdrenalineRushTalent: public Talent {
public:
    AdrenalineRushTalent(Character *pchar, TalentTree* tree);

private:
    AdrenalineRush* adrenaline_rush;

    void apply_rank_effect() override;
    void remove_rank_effect() override;
};

#endif // ADRENALINERUSHTALENT_H
