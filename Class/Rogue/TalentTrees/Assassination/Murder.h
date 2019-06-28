#pragma once

#include "Talent.h"

class TalentTree;

class Murder: public Talent {
public:
    Murder(Character *pchar, TalentTree* tree);
    ~Murder() override;

private:
    void apply_rank_effect() override;
    void remove_rank_effect() override;
};
