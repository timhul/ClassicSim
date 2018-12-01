#ifndef SWORDSPECIALIZATIONTALENTROGUE_H
#define SWORDSPECIALIZATIONTALENTROGUE_H

#include "Talent.h"

class SwordSpecialization;
class TalentTree;

class SwordSpecializationTalentRogue: public Talent {
public:
    SwordSpecializationTalentRogue(Character *pchar, TalentTree* tree);
    ~SwordSpecializationTalentRogue() override;

private:
    SwordSpecialization* sword_spec;

    void apply_rank_effect() override;
    void remove_rank_effect() override;
};

#endif // SWORDSPECIALIZATIONTALENTROGUE_H
