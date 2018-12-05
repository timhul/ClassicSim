#ifndef SEALFATETALENT_H
#define SEALFATETALENT_H

#include "Talent.h"

class SealFate;
class TalentTree;

class SealFateTalent: public Talent {
public:
    SealFateTalent(Character *pchar, TalentTree* tree);

private:
    SealFate* seal_fate;

    void apply_rank_effect() override;
    void remove_rank_effect() override;
};

#endif // SEALFATETALENT_H
