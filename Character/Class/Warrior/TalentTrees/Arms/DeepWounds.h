#ifndef DEEPWOUNDS_H
#define DEEPWOUNDS_H

#include "Talent.h"

class TalentTree;

class DeepWounds: public Talent {
    Q_OBJECT
public:
    DeepWounds(Character *pchar, TalentTree* tree);
    virtual ~DeepWounds();

    virtual void apply_rank_effect() override;
    virtual void remove_rank_effect() override;

private:
};

#endif // DEEPWOUNDS_H
