#pragma once

#include "Talent.h"

class TalentTree;

class Precision : public Talent {
public:
    Precision(Character* pchar, TalentTree* tree);
    ~Precision() override;

private:
    void apply_rank_effect() override;
    void remove_rank_effect() override;
};
