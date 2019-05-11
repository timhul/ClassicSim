#ifndef WEAPONEXPERTISE_H
#define WEAPONEXPERTISE_H

#include "Talent.h"

class TalentTree;

class WeaponExpertise: public Talent {
public:
    WeaponExpertise(Character *pchar, TalentTree* tree);
    ~WeaponExpertise() override;

private:
    void apply_rank_effect() override;
    void remove_rank_effect() override;
};

#endif // WEAPONEXPERTISE_H
