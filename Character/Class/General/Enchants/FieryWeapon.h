#ifndef FIERYWEAPON_H
#define FIERYWEAPON_H

#include "ProcPPM.h"

class FieryWeaponAttack;

class FieryWeapon: public ProcPPM {
public:
    FieryWeapon(Character* pchar, const QString &weapon_identifier, const int weapon);
    ~FieryWeapon() override;

    void proc_effect() override;

protected:
private:
    FieryWeaponAttack* fiery_weapon_attack;
};

#endif // FIERYWEAPON_H
