#ifndef DUALWIELDSPECIALIZATION_H
#define DUALWIELDSPECIALIZATION_H

#include "Talent.h"

class OffhandAttackWarrior;
class TalentTree;

class DualWieldSpecialization: public Talent {
    Q_OBJECT
public:
    DualWieldSpecialization(Character *pchar, TalentTree* tree);
    ~DualWieldSpecialization() override;

private:
    OffhandAttackWarrior* oh_attack;

    void apply_rank_effect() override;
    void remove_rank_effect() override;
};

#endif // DUALWIELDSPECIALIZATION_H
