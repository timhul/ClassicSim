#pragma once

#include "Talent.h"

class TalentTree;

class DaggerSpecialization: public Talent {
public:
    DaggerSpecialization(Character *pchar, TalentTree* tree);
    ~DaggerSpecialization() override;

private:
    void apply_rank_effect() override;
    void remove_rank_effect() override;
};
