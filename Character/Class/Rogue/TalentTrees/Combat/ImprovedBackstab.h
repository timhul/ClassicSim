#ifndef IMPROVEDBACKSTAB_H
#define IMPROVEDBACKSTAB_H

#include "Talent.h"

class Backstab;
class TalentTree;

class ImprovedBackstab: public Talent {
public:
    ImprovedBackstab(Character *pchar, TalentTree* tree);

private:
    Backstab* backstab;

    void apply_rank_effect() override;
    void remove_rank_effect() override;
};

#endif // IMPROVEDBACKSTAB_H
