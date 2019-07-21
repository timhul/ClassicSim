#pragma once

#include "ProcPPM.h"

class HolyStrength;

class Crusader: public ProcPPM {
public:
    Crusader(Character* pchar, const QString& weapon_identifier, const int weapon);
    ~Crusader() override;

    void proc_effect() override;

private:
    HolyStrength* holy_strength;
};
