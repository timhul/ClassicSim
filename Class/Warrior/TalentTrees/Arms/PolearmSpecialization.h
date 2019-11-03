#pragma once

#include "Talent.h"

class TalentTree;
class Warrior;

class PolearmSpecialization: public Talent {
public:
    PolearmSpecialization(Warrior* warrior, TalentTree* tree);
    ~PolearmSpecialization() override = default;

private:
    void apply_rank_effect() override;
    void remove_rank_effect() override;
};
