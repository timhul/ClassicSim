#ifndef IMPROVEDEXECUTE_H
#define IMPROVEDEXECUTE_H

#include "Talent.h"

class TalentTree;

class ImprovedExecute: public Talent {
    Q_OBJECT
public:
    ImprovedExecute(Character *pchar, TalentTree* tree);
    virtual ~ImprovedExecute();

    virtual void apply_rank_effect() override;
    virtual void remove_rank_effect() override;

private:
};

#endif // IMPROVEDEXECUTE_H
