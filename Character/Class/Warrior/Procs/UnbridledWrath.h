#ifndef UNBRIDLEDWRATH_H
#define UNBRIDLEDWRATH_H

#include "Proc.h"

class Warrior;

class UnbridledWrath: public Proc {
public:
    UnbridledWrath(Engine* engine, Character* pchar, CombatRoll* roll);
    ~UnbridledWrath() override;

    void proc_effect() override;
    void increase_effect_via_talent() override;
    void decrease_effect_via_talent() override;

protected:
private:
    Warrior* warr;
};

#endif // UNBRIDLEDWRATH_H
