#ifndef TWOHANDEDWEAPONSPECIALIZATION_H
#define TWOHANDEDWEAPONSPECIALIZATION_H

#include "Talent.h"

class TwoHandedWeaponSpecialization: public Talent {
    Q_OBJECT
public:
    TwoHandedWeaponSpecialization(Character *pchar);
    virtual ~TwoHandedWeaponSpecialization();

    virtual void apply_rank_effect() override;
    virtual void remove_rank_effect() override;

    QString get_requirement_string() const override;

private:
};

#endif // TWOHANDEDWEAPONSPECIALIZATION_H
