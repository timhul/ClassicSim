#pragma once

#include "Talent.h"

class TalentTree;

class Impale : public Talent {
public:
    Impale(Character* pchar, TalentTree* tree);
    ~Impale() override;

private:
    void apply_rank_effect() override;
    void remove_rank_effect() override;
};
