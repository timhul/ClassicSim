#ifndef IMPROVEDSLICEANDDICE_H
#define IMPROVEDSLICEANDDICE_H

#include "Talent.h"

class SliceAndDice;
class TalentTree;

class ImprovedSliceAndDice: public Talent {
public:
    ImprovedSliceAndDice(Character *pchar, TalentTree* tree);

private:
    SliceAndDice* slice_and_dice;

    void apply_rank_effect() override;
    void remove_rank_effect() override;
};

#endif // IMPROVEDSLICEANDDICE_H
