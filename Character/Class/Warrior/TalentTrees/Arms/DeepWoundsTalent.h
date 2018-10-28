#ifndef DEEPWOUNDSTALENT_H
#define DEEPWOUNDSTALENT_H

#include "Talent.h"

class DeepWounds;
class TalentTree;

class DeepWoundsTalent: public Talent {
public:
    DeepWoundsTalent(Character *pchar, TalentTree* tree);
    ~DeepWoundsTalent() override;

private:
    DeepWounds* deep_wounds;

    void apply_rank_effect() override;
    void remove_rank_effect() override;
};

#endif // DEEPWOUNDSTALENT_H
