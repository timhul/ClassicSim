#pragma once

#include "Talent.h"

class TalentTree;

class FistWeaponSpecialization : public Talent {
public:
    FistWeaponSpecialization(Character* pchar, TalentTree* tree);
    ~FistWeaponSpecialization() override;

private:
    void apply_rank_effect() override;
    void remove_rank_effect() override;
};
