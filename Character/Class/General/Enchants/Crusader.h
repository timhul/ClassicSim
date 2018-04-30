#ifndef CRUSADER_H
#define CRUSADER_H

#include "ProcPPM.h"

class Crusader: public ProcPPM {
public:
    Crusader(Engine* engine, Character* pchar, CombatRoll* roll, const int weapon);
    ~Crusader();

    void proc_effect() override;

protected:
private:
};

#endif // CRUSADER_H
