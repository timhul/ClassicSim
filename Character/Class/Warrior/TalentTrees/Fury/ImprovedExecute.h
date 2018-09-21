#ifndef IMPROVEDEXECUTE_H
#define IMPROVEDEXECUTE_H

#include "Talent.h"

class TalentTree;

class ImprovedExecute: public Talent {
    Q_OBJECT
public:
    ImprovedExecute(Character *pchar, TalentTree* tree);
    ~ImprovedExecute() override;

    void apply_rank_effect() override;
    void remove_rank_effect() override;

private:
};

#endif // IMPROVEDEXECUTE_H
