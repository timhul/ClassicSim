#pragma once

#include "Talent.h"

class TalentTree;

class PolearmSpecialization: public Talent {
public:
    PolearmSpecialization(Character *pchar, TalentTree* tree);
    ~PolearmSpecialization() override;

private:
    void apply_rank_effect() override;
    void remove_rank_effect() override;
};
