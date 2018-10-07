#ifndef DEEPWOUNDSTALENT_H
#define DEEPWOUNDSTALENT_H

#include "Talent.h"

class TalentTree;

class DeepWoundsTalent: public Talent {
    Q_OBJECT
public:
    DeepWoundsTalent(Character *pchar, TalentTree* tree);
    ~DeepWoundsTalent() override;

private:
    void apply_rank_effect() override;
    void remove_rank_effect() override;
};

#endif // DEEPWOUNDSTALENT_H
