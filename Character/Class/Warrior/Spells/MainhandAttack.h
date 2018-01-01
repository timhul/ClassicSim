#ifndef MAINHANDATTACK_H
#define MAINHANDATTACK_H

#include "Spell.h"

class MainhandAttack: public Spell {
public:
    MainhandAttack(Engine* engine, Character* pchar, CombatRoll* roll) :
        Spell("Mainhand Attack", engine, pchar, roll, 10.0, 0) {}

protected:
private:
    int spell_effect(const int) const override;
    void add_success_stats(std::string, const int, const int) const;
};

#endif // MAINHANDATTACK_H
