#ifndef MAINHANDATTACK_H
#define MAINHANDATTACK_H

#include "Spell.h"

class MainhandAttack: public Spell {
public:
    MainhandAttack(Engine* engine, Character* pchar) :
        Spell("Mainhand Attack", engine, pchar, 10.0, 0) {}

protected:
private:
    int spell_effect(const int) const override;
};

#endif // MAINHANDATTACK_H
