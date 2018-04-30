#ifndef FIERYWEAPON_H
#define FIERYWEAPON_H

#include "ProcPPM.h"

class FieryWeapon: public ProcPPM {
public:
    FieryWeapon(Engine* engine, Character* pchar, CombatRoll* roll, const int weapon);
    ~FieryWeapon();

    void proc_effect() override;

protected:
private:
};

#endif // FIERYWEAPON_H
