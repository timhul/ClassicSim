#pragma once

#include "Talent.h"

class TalentTree;
class Warrior;

class TacticalMastery: public Talent {
public:
    TacticalMastery(Warrior* warrior, TalentTree* tree);

private:
    Warrior* warrior;

    void apply_rank_effect() override;
    void remove_rank_effect() override;
};
