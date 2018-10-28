#ifndef BLOODTHIRSTTALENT_H
#define BLOODTHIRSTTALENT_H

#include "Talent.h"

class Bloodthirst;
class TalentTree;

class BloodthirstTalent: public Talent {
public:
    BloodthirstTalent(Character *pchar, TalentTree* tree);
    ~BloodthirstTalent() override;

private:
    Bloodthirst* bloodthirst;

    void apply_rank_effect() override;
    void remove_rank_effect() override;
};

#endif // BLOODTHIRSTTALENT_H
