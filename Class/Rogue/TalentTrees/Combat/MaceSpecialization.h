#pragma once

#include "Talent.h"

class TalentTree;

class MaceSpecialization: public Talent {
public:
    MaceSpecialization(Character *pchar, TalentTree* tree);
    ~MaceSpecialization() override;

private:
    void apply_rank_effect() override;
    void remove_rank_effect() override;
};
