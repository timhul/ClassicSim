#pragma once

#include "Talent.h"

class TalentTree;
class Warrior;

class AxeSpecialization : public Talent {
public:
    AxeSpecialization(Warrior* warrior, TalentTree* tree);
    ~AxeSpecialization() override = default;

private:
    void apply_rank_effect() override;
    void remove_rank_effect() override;
};
