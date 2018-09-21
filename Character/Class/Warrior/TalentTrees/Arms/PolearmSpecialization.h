#ifndef POLEARMSPECIALIZATION_H
#define POLEARMSPECIALIZATION_H

#include "Talent.h"

class TalentTree;

class PolearmSpecialization: public Talent {
    Q_OBJECT
public:
    PolearmSpecialization(Character *pchar, TalentTree* tree);
    ~PolearmSpecialization() override;

    void apply_rank_effect() override;
    void remove_rank_effect() override;

private:
};

#endif // POLEARMSPECIALIZATION_H
