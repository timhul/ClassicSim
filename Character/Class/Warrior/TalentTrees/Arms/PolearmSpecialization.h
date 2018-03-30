#ifndef POLEARMSPECIALIZATION_H
#define POLEARMSPECIALIZATION_H

#include "Talent.h"

class TalentTree;

class PolearmSpecialization: public Talent {
    Q_OBJECT
public:
    PolearmSpecialization(Character *pchar, TalentTree* tree);
    virtual ~PolearmSpecialization();

    virtual void apply_rank_effect() override;
    virtual void remove_rank_effect() override;

private:
};

#endif // POLEARMSPECIALIZATION_H
