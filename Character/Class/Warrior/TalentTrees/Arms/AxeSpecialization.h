#ifndef AXESPECIALIZATION_H
#define AXESPECIALIZATION_H

#include "Talent.h"

class TalentTree;

class AxeSpecialization: public Talent {
    Q_OBJECT
public:
    AxeSpecialization(Character *pchar, TalentTree* tree);
    ~AxeSpecialization() override;

private:
    void apply_rank_effect() override;
    void remove_rank_effect() override;
};

#endif // AXESPECIALIZATION_H
