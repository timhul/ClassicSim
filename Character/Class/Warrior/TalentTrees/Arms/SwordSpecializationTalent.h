#ifndef SWORDSPECIALIZATIONTALENT_H
#define SWORDSPECIALIZATIONTALENT_H

#include "Talent.h"

class TalentTree;

class SwordSpecializationTalent: public Talent {
    Q_OBJECT
public:
    SwordSpecializationTalent(Character *pchar, TalentTree* tree);
    ~SwordSpecializationTalent() override;

private:
    void apply_rank_effect() override;
    void remove_rank_effect() override;
};

#endif // SWORDSPECIALIZATIONTALENT_H
