#ifndef IMPROVEDEXECUTE_H
#define IMPROVEDEXECUTE_H

#include "Talent.h"

class TalentTree;

class ImprovedExecute: public Talent {
    Q_OBJECT
public:
    ImprovedExecute(Character *pchar, TalentTree* tree);
    ~ImprovedExecute() override;

private:
    void apply_rank_effect() override;
    void remove_rank_effect() override;
};

#endif // IMPROVEDEXECUTE_H
