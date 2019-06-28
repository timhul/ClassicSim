#pragma once

#include "Talent.h"

class TalentTree;
class Warrior;

class TacticalMastery: public Talent {
public:
    TacticalMastery(Character* pchar, TalentTree* tree);

private:
    Warrior* warr;

    void apply_rank_effect() override;
    void remove_rank_effect() override;
};
