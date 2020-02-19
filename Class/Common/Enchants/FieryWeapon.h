#pragma once

#include "ProcPPM.h"

class InstantSpellAttack;

class FieryWeapon : public ProcPPM {
public:
    FieryWeapon(Character* pchar, const QString& weapon_identifier, const int weapon);
    ~FieryWeapon() override;

    void proc_effect() override;

private:
    InstantSpellAttack* fiery_weapon_attack;
};
