#pragma once

#include "Talent.h"

class TalentTree;

class AxeSpecialization: public Talent {
public:
    AxeSpecialization(Character *pchar, TalentTree* tree);
    ~AxeSpecialization() override;

private:
    void apply_rank_effect() override;
    void remove_rank_effect() override;
};
