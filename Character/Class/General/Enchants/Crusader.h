#ifndef CRUSADER_H
#define CRUSADER_H

#include "ProcPPM.h"

class HolyStrength;

class Crusader: public ProcPPM {
public:
    Crusader(Character* pchar, const int weapon);
    ~Crusader() override;

    void proc_effect() override;

protected:
private:
    HolyStrength* holy_strength;
};

#endif // CRUSADER_H
