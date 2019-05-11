#ifndef SWORDSPECIALIZATIONTALENT_H
#define SWORDSPECIALIZATIONTALENT_H

#include "Talent.h"

class SwordSpecialization;
class TalentTree;
class Warrior;

class SwordSpecializationTalent: public Talent {
public:
    SwordSpecializationTalent(Warrior* pchar, TalentTree* tree);
    ~SwordSpecializationTalent() override;

private:
    SwordSpecialization* sword_spec;

    void apply_rank_effect() override;
    void remove_rank_effect() override;
};

#endif // SWORDSPECIALIZATIONTALENT_H
