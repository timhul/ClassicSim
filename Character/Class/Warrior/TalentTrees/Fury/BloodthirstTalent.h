#ifndef BLOODTHIRSTTALENT_H
#define BLOODTHIRSTTALENT_H

#include "Talent.h"

class TalentTree;

class BloodthirstTalent: public Talent {
    Q_OBJECT
public:
    BloodthirstTalent(Character *pchar, TalentTree* tree);
    ~BloodthirstTalent() override;

private:
    void apply_rank_effect() override;
    void remove_rank_effect() override;
};

#endif // BLOODTHIRSTTALENT_H
