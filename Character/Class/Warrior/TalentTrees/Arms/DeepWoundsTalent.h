#ifndef DEEPWOUNDS_H
#define DEEPWOUNDS_H

#include "Talent.h"

class TalentTree;

class DeepWoundsTalent: public Talent {
    Q_OBJECT
public:
    DeepWoundsTalent(Character *pchar, TalentTree* tree);
    virtual ~DeepWoundsTalent();

    virtual void apply_rank_effect() override;
    virtual void remove_rank_effect() override;

private:
};

#endif // DEEPWOUNDS_H
