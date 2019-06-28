#pragma once

#include "Talent.h"

class TalentTree;

class Malice: public Talent {
public:
    Malice(Character *pchar, TalentTree* tree);
    ~Malice() override;

private:
    void apply_rank_effect() override;
    void remove_rank_effect() override;
};
