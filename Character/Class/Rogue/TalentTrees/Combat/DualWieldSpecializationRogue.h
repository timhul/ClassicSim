#ifndef DUALWIELDSPECIALIZATIONROGUE_H
#define DUALWIELDSPECIALIZATIONROGUE_H

#include "Talent.h"

class OffhandAttackRogue;
class TalentTree;

class DualWieldSpecializationRogue: public Talent {
public:
    DualWieldSpecializationRogue(Character *pchar, TalentTree* tree);
    ~DualWieldSpecializationRogue() override;

private:
    OffhandAttackRogue* oh_attack;

    void apply_rank_effect() override;
    void remove_rank_effect() override;
};

#endif // DUALWIELDSPECIALIZATIONROGUE_H
