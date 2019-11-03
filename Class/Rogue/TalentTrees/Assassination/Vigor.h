#pragma once

#include "Talent.h"

class Rogue;
class TalentTree;

class Vigor: public Talent {
public:
    Vigor(Rogue* rogue, TalentTree* tree);
    ~Vigor() override = default;

private:
    Rogue* rogue;

    void apply_rank_effect() override;
    void remove_rank_effect() override;
};
