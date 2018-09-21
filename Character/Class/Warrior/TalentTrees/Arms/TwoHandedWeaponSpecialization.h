#ifndef TWOHANDEDWEAPONSPECIALIZATION_H
#define TWOHANDEDWEAPONSPECIALIZATION_H

#include "Talent.h"

class TalentTree;

class TwoHandedWeaponSpecialization: public Talent {
    Q_OBJECT
public:
    TwoHandedWeaponSpecialization(Character *pchar, TalentTree* tree);
    ~TwoHandedWeaponSpecialization() override;

    void apply_rank_effect() override;
    void remove_rank_effect() override;

private:
};

#endif // TWOHANDEDWEAPONSPECIALIZATION_H
