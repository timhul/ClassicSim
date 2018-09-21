#ifndef AXESPECIALIZATION_H
#define AXESPECIALIZATION_H

#include "Talent.h"

class TalentTree;

class AxeSpecialization: public Talent {
    Q_OBJECT
public:
    AxeSpecialization(Character *pchar, TalentTree* tree);
    ~AxeSpecialization() override;

    void apply_rank_effect() override;
    void remove_rank_effect() override;

private:
};

#endif // AXESPECIALIZATION_H
