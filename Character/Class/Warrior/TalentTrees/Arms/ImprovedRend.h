#ifndef IMPROVEDREND_H
#define IMPROVEDREND_H

#include "Talent.h"

class TalentTree;

class ImprovedRend: public Talent {
    Q_OBJECT
public:
    ImprovedRend(Character *pchar, TalentTree* tree);
    ~ImprovedRend() override;

private:
    void apply_rank_effect() override;
    void remove_rank_effect() override;
};

#endif // IMPROVEDREND_H
