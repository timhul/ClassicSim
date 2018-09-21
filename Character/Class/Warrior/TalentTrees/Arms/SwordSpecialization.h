#ifndef SWORDSPECIALIZATION_H
#define SWORDSPECIALIZATION_H

#include "Talent.h"

class TalentTree;

class SwordSpecialization: public Talent {
    Q_OBJECT
public:
    SwordSpecialization(Character *pchar, TalentTree* tree);
    ~SwordSpecialization() override;

    void apply_rank_effect() override;
    void remove_rank_effect() override;

private:
};

#endif // SWORDSPECIALIZATION_H
