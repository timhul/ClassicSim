#ifndef MAINHANDATTACK_H
#define MAINHANDATTACK_H

#include "Spell.h"

class Warrior;

class MainhandAttack: public Spell {
public:
    MainhandAttack(Engine* engine, Character *pchar, CombatRoll* roll);

    float get_next_expected_use() const;
    void update_next_expected_use(const float);

protected:
private:
    int spell_effect(const int) const override;
    Warrior* pchar;
    float next_expected_use;
};

#endif // MAINHANDATTACK_H
