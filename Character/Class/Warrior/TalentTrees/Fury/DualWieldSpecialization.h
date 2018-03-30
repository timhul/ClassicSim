#ifndef DUALWIELDSPECIALIZATION_H
#define DUALWIELDSPECIALIZATION_H

#include "Talent.h"

class TalentTree;

class DualWieldSpecialization: public Talent {
    Q_OBJECT
public:
    DualWieldSpecialization(Character *pchar, TalentTree* tree);
    virtual ~DualWieldSpecialization();

    virtual void apply_rank_effect() override;
    virtual void remove_rank_effect() override;

private:
};

#endif // DUALWIELDSPECIALIZATION_H
