#ifndef TWOHANDEDWEAPONSPECIALIZATION_H
#define TWOHANDEDWEAPONSPECIALIZATION_H

#include "Talent.h"

class TalentTree;

class TwoHandedWeaponSpecialization: public Talent {
    Q_OBJECT
public:
    TwoHandedWeaponSpecialization(Character *pchar, TalentTree* tree);
    virtual ~TwoHandedWeaponSpecialization();

    virtual void apply_rank_effect() override;
    virtual void remove_rank_effect() override;

private:
};

#endif // TWOHANDEDWEAPONSPECIALIZATION_H
