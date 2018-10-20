#ifndef FIERYWEAPON_H
#define FIERYWEAPON_H

#include "ProcPPM.h"

class InstantSpellAttack;

class FieryWeapon: public ProcPPM {
public:
    FieryWeapon(Character* pchar, const QString &weapon_identifier, const int weapon);
    ~FieryWeapon() override;

    void proc_effect() override;

protected:
private:
    InstantSpellAttack* fiery_weapon_attack;
};

#endif // FIERYWEAPON_H
